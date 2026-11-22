/**
 * @file ICartoesAtividades.hpp
 * @brief Interface do servico de cartoes de atividade.
 */

#ifndef ICARTOESATIVIDADES_HPP
#define ICARTOESATIVIDADES_HPP

#include "../entidades/CartaoAtividade.hpp"
#include <vector>

/**
 * @class ICartoesAtividades
 * @brief Interface para operacoes relacionadas a cartoes de atividade.
 *
 * Define o CRUD de cartoes, a movimentacao entre estados e o
 * calculo dos indicadores do quadro (WIP, lead time e cycle time).
 */
class ICartoesAtividades
{
public:
    /**
     * @brief Destrutor virtual.
     */
    virtual ~ICartoesAtividades() = default;

    /**
     * @brief Cadastra um cartao de atividade.
     * @param cartao Cartao a ser cadastrado.
     */
    virtual void cadastrar(const CartaoAtividade &cartao) = 0;

    /**
     * @brief Consulta um cartao pelo identificador.
     * @param identificador Identificador do cartao.
     * @return Cartao encontrado.
     */
    virtual CartaoAtividade consultar(const Identificador &identificador) = 0;

    /**
     * @brief Lista todos os cartoes cadastrados.
     * @return Vetor com os cartoes cadastrados.
     */
    virtual std::vector<CartaoAtividade> listar() = 0;

    /**
     * @brief Atualiza os dados de um cartao.
     * @param cartao Cartao com os dados atualizados.
     */
    virtual void atualizar(const CartaoAtividade &cartao) = 0;

    /**
     * @brief Remove um cartao pelo identificador.
     * @param identificador Identificador do cartao.
     */
    virtual void remover(const Identificador &identificador) = 0;

    /**
     * @brief Move um cartao para outro estado.
     * @param identificador Identificador do cartao.
     * @param novoEstado Estado de destino (FAZENDO ou FEITO).
     * @param momento Data e hora da movimentacao.
     */
    virtual void mover(
        const Identificador &identificador,
        const Estado &novoEstado,
        const Timestamp &momento) = 0;

    /**
     * @brief Calcula o WIP atual de um quadro.
     * @param quadro Identificador do quadro.
     * @return Quantidade de cartoes no estado FAZENDO.
     */
    virtual int calcularWIP(const Identificador &quadro) = 0;

    /**
     * @brief Calcula o lead time medio de um quadro.
     *
     * Lead time e o tempo entre a entrada do cartao e sua conclusao.
     *
     * @param quadro Identificador do quadro.
     * @return Lead time medio, em minutos, dos cartoes FEITO.
     */
    virtual double calcularLeadTimeMedio(
        const Identificador &quadro) = 0;

    /**
     * @brief Calcula o cycle time medio de um quadro.
     *
     * Cycle time e o tempo entre o inicio da execucao e a conclusao.
     *
     * @param quadro Identificador do quadro.
     * @return Cycle time medio, em minutos, dos cartoes FEITO.
     */
    virtual double calcularCycleTimeMedio(
        const Identificador &quadro) = 0;
};

#endif
