/**
 * @file IQuadros.hpp
 * @brief Interface do servico de quadros.
 */

#ifndef IQUADROS_HPP
#define IQUADROS_HPP

#include "../entidades/Quadro.hpp"
#include <vector>

/**
 * @class IQuadros
 * @brief Interface para operacoes relacionadas a quadros.
 */
class IQuadros {
public:
    /**
     * @brief Destrutor virtual.
     */
    virtual ~IQuadros() = default;

    /**
     * @brief Cadastra um quadro.
     * @param quadro Quadro a ser cadastrado.
     */
    virtual void cadastrar(const Quadro& quadro) = 0;

    /**
     * @brief Consulta um quadro pelo identificador.
     * @param identificador Identificador do quadro.
     * @return Quadro encontrado.
     */
    virtual Quadro consultar(const Identificador& identificador) = 0;

    /**
     * @brief Lista todos os quadros cadastrados.
     * @return Vetor com os quadros cadastrados.
     */
    virtual std::vector<Quadro> listar() = 0;

    /**
     * @brief Atualiza os dados de um quadro.
     * @param quadro Quadro com os dados atualizados.
     */
    virtual void atualizar(const Quadro& quadro) = 0;

    /**
     * @brief Remove um quadro pelo identificador.
     * @param identificador Identificador do quadro.
     */
    virtual void remover(const Identificador& identificador) = 0;
};

#endif
