/**
 * @file ServicoCartoesAtividades.hpp
 * @brief Implementacao do servico de cartoes de atividade.
 */

#ifndef SERVICOCARTOESATIVIDADES_HPP
#define SERVICOCARTOESATIVIDADES_HPP

#include "../interfaces/ICartoesAtividades.hpp"
#include "../containers/CartoesAtividades.hpp"
#include "../containers/Quadros.hpp"

#include <stdexcept>
#include <string>
#include <vector>
#include <ctime>

/**
 * @class ServicoCartoesAtividades
 * @brief Implementa as regras de negocio dos cartoes de atividade.
 *
 * Aplica as regras do Kanban antes de acessar o banco:
 * - todo cartao e cadastrado no estado A FAZER;
 * - o estado so muda pelo metodo mover();
 * - o limite WIP do quadro e respeitado ao entrar em FAZENDO;
 * - calcula WIP, lead time medio e cycle time medio.
 */
class ServicoCartoesAtividades : public ICartoesAtividades
{
private:
    /**
     * @brief Container responsavel pela persistencia dos cartoes.
     */
    CartoesAtividades &repositorio;

    /**
     * @brief Container de quadros, usado para consultar o limite WIP.
     */
    Quadros &repositorioQuadros;

    /**
     * @brief Verifica se o quadro do cartao ainda comporta mais um
     *        cartao em FAZENDO.
     * @param cartao Cartao que sera movido para FAZENDO.
     * @param ignorarIdentificador Identificador de um cartao que nao
     *        deve entrar na contagem.
     * @throw std::runtime_error Se o limite WIP do quadro for atingido.
     */
    void validarLimiteWIP(
        const CartaoAtividade &cartao,
        const std::string &ignorarIdentificador = "")
    {
        Quadro quadro = repositorioQuadros.consultar(cartao.getQuadro());
        int limite = quadro.getLimite().getValor();
        int quantidade = 0;

        std::vector<CartaoAtividade> cartoes = repositorio.listar();

        for (const CartaoAtividade &existente : cartoes)
        {
            bool mesmoQuadro =
                existente.getQuadro().getIdentificador() ==
                cartao.getQuadro().getIdentificador();

            bool estaFazendo =
                existente.getEstado().getEstado() == "FAZENDO";

            bool naoIgnorar =
                existente.getIdentificador().getIdentificador() !=
                ignorarIdentificador;

            if (mesmoQuadro && estaFazendo && naoIgnorar)
            {
                quantidade++;
            }
        }

        if (quantidade >= limite)
        {
            throw std::runtime_error("Limite de WIP do quadro atingido.");
        }
    }

    /**
     * @brief Converte um timestamp para minutos desde a epoca Unix.
     * @param timestamp Data e hora no formato DD-MMM-AAAA-HH:MM.
     * @return Quantidade de minutos correspondente.
     * @throw std::invalid_argument Se o mes for invalido.
     * @throw std::runtime_error Se a conversao da data falhar.
     */
    long long converterParaMinutos(const Timestamp &timestamp)
    {
        std::string valor = timestamp.getTimestamp();

        int dia = std::stoi(valor.substr(0, 2));
        std::string mes = valor.substr(3, 3);
        int ano = std::stoi(valor.substr(7, 4));
        int hora = std::stoi(valor.substr(12, 2));
        int minuto = std::stoi(valor.substr(15, 2));

        int numeroMes;

        if (mes == "JAN")
            numeroMes = 0;
        else if (mes == "FEV")
            numeroMes = 1;
        else if (mes == "MAR")
            numeroMes = 2;
        else if (mes == "ABR")
            numeroMes = 3;
        else if (mes == "MAI")
            numeroMes = 4;
        else if (mes == "JUN")
            numeroMes = 5;
        else if (mes == "JUL")
            numeroMes = 6;
        else if (mes == "AGO")
            numeroMes = 7;
        else if (mes == "SET")
            numeroMes = 8;
        else if (mes == "OUT")
            numeroMes = 9;
        else if (mes == "NOV")
            numeroMes = 10;
        else if (mes == "DEZ")
            numeroMes = 11;
        else
        {
            throw std::invalid_argument("Mes invalido.");
        }

        std::tm data = {};
        data.tm_mday = dia;
        data.tm_mon = numeroMes;
        data.tm_year = ano - 1900;
        data.tm_hour = hora;
        data.tm_min = minuto;
        data.tm_isdst = -1;

        std::time_t resultado = std::mktime(&data);

        if (resultado == static_cast<std::time_t>(-1))
        {
            throw std::runtime_error("Nao foi possivel converter a data.");
        }

        return static_cast<long long>(resultado / 60);
    }

    /**
     * @brief Calcula o tempo medio dos cartoes concluidos de um quadro.
     * @param quadro Identificador do quadro.
     * @param ciclo true para cycle time (inicio ate termino);
     *        false para lead time (entrada ate termino).
     * @return Tempo medio em minutos, ou 0 se nao houver cartoes FEITO.
     * @throw std::runtime_error Se a data de conclusao for anterior
     *        a data inicial.
     */
    double calcularTempoMedio(
        const Identificador &quadro,
        bool ciclo)
    {
        std::vector<CartaoAtividade> cartoes = repositorio.listar();

        long long soma = 0;
        int quantidade = 0;

        for (const CartaoAtividade &cartao : cartoes)
        {
            bool mesmoQuadro =
                cartao.getQuadro().getIdentificador() ==
                quadro.getIdentificador();

            bool concluido =
                cartao.getEstado().getEstado() == "FEITO";

            if (!mesmoQuadro || !concluido)
            {
                continue;
            }

            Timestamp inicio;

            if (ciclo)
            {
                inicio = cartao.getInicio();
            }
            else
            {
                inicio = cartao.getEntrada();
            }

            long long momentoInicial = converterParaMinutos(inicio);
            long long momentoFinal =
                converterParaMinutos(cartao.getTermino());

            if (momentoFinal < momentoInicial)
            {
                throw std::runtime_error(
                    "Data de conclusao anterior a data inicial.");
            }

            soma += momentoFinal - momentoInicial;
            quantidade++;
        }

        if (quantidade == 0)
        {
            return 0.0;
        }

        return static_cast<double>(soma) / quantidade;
    }

public:
    /**
     * @brief Construtor do servico de cartoes.
     * @param cartoes Container de cartoes de atividade.
     * @param quadros Container de quadros.
     */
    explicit ServicoCartoesAtividades(
        CartoesAtividades &cartoes,
        Quadros &quadros) : repositorio(cartoes), repositorioQuadros(quadros) {}

    /**
     * @brief Cadastra um cartao de atividade.
     * @param cartao Cartao a ser cadastrado.
     * @throw std::invalid_argument Se o cartao nao estiver em A FAZER.
     */
    void cadastrar(const CartaoAtividade &cartao) override
    {
        if (cartao.getEstado().getEstado() != "A FAZER")
        {
            throw std::invalid_argument(
                "Todo cartao deve ser cadastrado em A FAZER.");
        }

        repositorio.inserir(cartao);
    }

    /**
     * @brief Consulta um cartao pelo identificador.
     * @param identificador Identificador do cartao.
     * @return Cartao encontrado.
     */
    CartaoAtividade consultar(
        const Identificador &identificador) override
    {
        return repositorio.consultar(identificador);
    }

    /**
     * @brief Lista todos os cartoes cadastrados.
     * @return Vetor com os cartoes cadastrados.
     */
    std::vector<CartaoAtividade> listar() override
    {
        return repositorio.listar();
    }

    /**
     * @brief Atualiza nome, descricao, prioridade, tamanho e
     *        desenvolvedor de um cartao.
     *
     * Estado, timestamps e quadro sao preservados.
     *
     * @param cartao Cartao com os dados atualizados.
     * @throw std::invalid_argument Se houver tentativa de alterar o estado.
     */
    void atualizar(const CartaoAtividade &cartao) override
    {
        CartaoAtividade atual =
            repositorio.consultar(cartao.getIdentificador());

        if (atual.getEstado().getEstado() !=
            cartao.getEstado().getEstado())
        {
            throw std::invalid_argument(
                "Utilize o metodo mover para alterar o estado.");
        }

        // Preserva os dados que nao podem ser alterados.
        CartaoAtividade atualizado = atual;

        atualizado.setNome(cartao.getNome());
        atualizado.setDescricao(cartao.getDescricao());
        atualizado.setPrioridade(cartao.getPrioridade());
        atualizado.setTamanho(cartao.getTamanho());
        atualizado.setDesenvolvedor(cartao.getDesenvolvedor());

        repositorio.atualizar(atualizado);
    }

    /**
     * @brief Remove um cartao pelo identificador.
     * @param identificador Identificador do cartao.
     */
    void remover(const Identificador &identificador) override
    {
        repositorio.remover(identificador);
    }

    /**
     * @brief Move um cartao para outro estado, respeitando o limite WIP.
     * @param identificador Identificador do cartao.
     * @param novoEstado Estado de destino (FAZENDO ou FEITO).
     * @param momento Data e hora da movimentacao.
     * @throw std::runtime_error Se o limite WIP do quadro for atingido.
     */
    void mover(
        const Identificador &identificador,
        const Estado &novoEstado,
        const Timestamp &momento) override
    {
        CartaoAtividade cartao = repositorio.consultar(identificador);

        bool entrandoEmFazendo =
            cartao.getEstado().getEstado() == "A FAZER" &&
            novoEstado.getEstado() == "FAZENDO";

        if (entrandoEmFazendo)
        {
            validarLimiteWIP(
                cartao,
                identificador.getIdentificador());
        }

        repositorio.mover(identificador, novoEstado, momento);
    }

    /**
     * @brief Calcula o WIP atual de um quadro.
     * @param quadro Identificador do quadro.
     * @return Quantidade de cartoes no estado FAZENDO.
     */
    int calcularWIP(const Identificador &quadro) override
    {
        std::vector<CartaoAtividade> cartoes = repositorio.listar();

        int quantidade = 0;

        for (const CartaoAtividade &cartao : cartoes)
        {
            bool mesmoQuadro =
                cartao.getQuadro().getIdentificador() ==
                quadro.getIdentificador();

            bool estaFazendo =
                cartao.getEstado().getEstado() == "FAZENDO";

            if (mesmoQuadro && estaFazendo)
            {
                quantidade++;
            }
        }

        return quantidade;
    }

    /**
     * @brief Calcula o lead time medio de um quadro.
     * @param quadro Identificador do quadro.
     * @return Lead time medio em minutos.
     */
    double calcularLeadTimeMedio(
        const Identificador &quadro) override
    {
        return calcularTempoMedio(quadro, false);
    }

    /**
     * @brief Calcula o cycle time medio de um quadro.
     * @param quadro Identificador do quadro.
     * @return Cycle time medio em minutos.
     */
    double calcularCycleTimeMedio(
        const Identificador &quadro) override
    {
        return calcularTempoMedio(quadro, true);
    }
};

#endif
