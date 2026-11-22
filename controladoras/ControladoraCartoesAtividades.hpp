/**
 * @file ControladoraCartoesAtividades.hpp
 * @brief Controladora das operacoes de cartoes de atividade.
 */

#ifndef CONTROLADORA_CARTOES_ATIVIDADES_HPP
#define CONTROLADORA_CARTOES_ATIVIDADES_HPP

#include "../interfaces/ICartoesAtividades.hpp"
#include "../dominio/papel.hpp"

#include <stdexcept>
#include <vector>

/**
 * @class ControladoraCartoesAtividades
 * @brief Controla as operacoes relacionadas aos cartoes de atividade.
 *
 * Verifica as permissoes do usuario e encaminha as operacoes
 * para o servico de cartoes.
 *
 * - O gestor pode cadastrar, atualizar e remover cartoes.
 * - O desenvolvedor pode mover cartoes e consultar os indicadores.
 * - Ambos podem consultar e listar cartoes.
 */
class ControladoraCartoesAtividades
{
private:
    /**
     * @brief Referencia para a interface do servico de cartoes.
     */
    ICartoesAtividades &servico;

    /**
     * @brief Verifica se o usuario possui papel de gestor.
     * @param papel Papel do usuario autenticado.
     * @throw std::runtime_error Caso o usuario nao seja gestor.
     */
    void exigirGestor(const Papel &papel)
    {
        if (papel.getPapel() != "GESTOR")
        {
            throw std::runtime_error(
                "Operacao permitida somente para o gestor.");
        }
    }

    /**
     * @brief Verifica se o usuario possui papel de desenvolvedor.
     * @param papel Papel do usuario autenticado.
     * @throw std::runtime_error Caso o usuario nao seja desenvolvedor.
     */
    void exigirDesenvolvedor(const Papel &papel)
    {
        if (papel.getPapel() != "DESENVOLVEDOR")
        {
            throw std::runtime_error(
                "Operacao permitida somente para o desenvolvedor.");
        }
    }

public:
    /**
     * @brief Construtor da controladora de cartoes.
     * @param servicoCartoes Interface do servico de cartoes.
     */
    explicit ControladoraCartoesAtividades(
        ICartoesAtividades &servicoCartoes) : servico(servicoCartoes) {}

    /**
     * @brief Cadastra um novo cartao.
     * @param papel Papel do usuario autenticado.
     * @param cartao Cartao que sera cadastrado.
     * @throw std::runtime_error Caso o usuario nao seja gestor.
     */
    void cadastrar(
        const Papel &papel,
        const CartaoAtividade &cartao)
    {
        exigirGestor(papel);
        servico.cadastrar(cartao);
    }

    /**
     * @brief Consulta um cartao pelo identificador.
     * @param papel Papel do usuario autenticado.
     * @param identificador Identificador do cartao.
     * @return Cartao encontrado.
     * @throw std::runtime_error Caso o papel nao tenha permissao.
     */
    CartaoAtividade consultar(
        const Papel &papel,
        const Identificador &identificador)
    {
        if (papel.getPapel() != "GESTOR" &&
            papel.getPapel() != "DESENVOLVEDOR")
        {
            throw std::runtime_error("Papel sem permissao.");
        }

        return servico.consultar(identificador);
    }

    /**
     * @brief Lista os cartoes cadastrados.
     * @param papel Papel do usuario autenticado.
     * @return Vetor com os cartoes cadastrados.
     * @throw std::runtime_error Caso o papel nao tenha permissao.
     */
    std::vector<CartaoAtividade> listar(const Papel &papel)
    {
        if (papel.getPapel() != "GESTOR" &&
            papel.getPapel() != "DESENVOLVEDOR")
        {
            throw std::runtime_error("Papel sem permissao.");
        }

        return servico.listar();
    }

    /**
     * @brief Atualiza os dados de um cartao.
     * @param papel Papel do usuario autenticado.
     * @param cartao Cartao com os dados atualizados.
     * @throw std::runtime_error Caso o usuario nao seja gestor.
     */
    void atualizar(
        const Papel &papel,
        const CartaoAtividade &cartao)
    {
        exigirGestor(papel);
        servico.atualizar(cartao);
    }

    /**
     * @brief Remove um cartao pelo identificador.
     * @param papel Papel do usuario autenticado.
     * @param identificador Identificador do cartao.
     * @throw std::runtime_error Caso o usuario nao seja gestor.
     */
    void remover(
        const Papel &papel,
        const Identificador &identificador)
    {
        exigirGestor(papel);
        servico.remover(identificador);
    }

    /**
     * @brief Move um cartao para outro estado.
     * @param papel Papel do usuario autenticado.
     * @param identificador Identificador do cartao.
     * @param novoEstado Estado de destino (FAZENDO ou FEITO).
     * @param momento Data e hora da movimentacao.
     * @throw std::runtime_error Caso o usuario nao seja desenvolvedor.
     */
    void mover(
        const Papel &papel,
        const Identificador &identificador,
        const Estado &novoEstado,
        const Timestamp &momento)
    {
        exigirDesenvolvedor(papel);
        servico.mover(identificador, novoEstado, momento);
    }

    /**
     * @brief Calcula o WIP atual de um quadro.
     * @param papel Papel do usuario autenticado.
     * @param quadro Identificador do quadro.
     * @return Quantidade de cartoes no estado FAZENDO.
     * @throw std::runtime_error Caso o usuario nao seja desenvolvedor.
     */
    int calcularWIP(
        const Papel &papel,
        const Identificador &quadro)
    {
        exigirDesenvolvedor(papel);
        return servico.calcularWIP(quadro);
    }

    /**
     * @brief Calcula o lead time medio de um quadro.
     * @param papel Papel do usuario autenticado.
     * @param quadro Identificador do quadro.
     * @return Lead time medio em minutos.
     * @throw std::runtime_error Caso o usuario nao seja desenvolvedor.
     */
    double calcularLeadTimeMedio(
        const Papel &papel,
        const Identificador &quadro)
    {
        exigirDesenvolvedor(papel);
        return servico.calcularLeadTimeMedio(quadro);
    }

    /**
     * @brief Calcula o cycle time medio de um quadro.
     * @param papel Papel do usuario autenticado.
     * @param quadro Identificador do quadro.
     * @return Cycle time medio em minutos.
     * @throw std::runtime_error Caso o usuario nao seja desenvolvedor.
     */
    double calcularCycleTimeMedio(
        const Papel &papel,
        const Identificador &quadro)
    {
        exigirDesenvolvedor(papel);
        return servico.calcularCycleTimeMedio(quadro);
    }
};

#endif
