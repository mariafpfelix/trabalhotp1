/**
 * @file IProjetos.hpp
 * @brief Interface do servico de projetos.
 */

#ifndef IPROJETOS_HPP
#define IPROJETOS_HPP

#include "../entidades/Projeto.hpp"
#include <vector>

/**
 * @class IProjetos
 * @brief Interface para operacoes relacionadas a projetos.
 */
class IProjetos {
public:
    /**
     * @brief Destrutor virtual.
     */
    virtual ~IProjetos() = default;

    /**
     * @brief Cadastra um projeto.
     * @param projeto Projeto a ser cadastrado.
     */
    virtual void cadastrar(const Projeto& projeto) = 0;

    /**
     * @brief Consulta um projeto pelo identificador.
     * @param identificador Identificador do projeto.
     * @return Projeto encontrado.
     */
    virtual Projeto consultar(const Identificador& identificador) = 0;

    /**
     * @brief Lista todos os projetos cadastrados.
     * @return Vetor com os projetos cadastrados.
     */
    virtual std::vector<Projeto> listar() = 0;

    /**
     * @brief Atualiza os dados de um projeto.
     * @param projeto Projeto com os dados atualizados.
     */
    virtual void atualizar(const Projeto& projeto) = 0;

    /**
     * @brief Remove um projeto pelo identificador.
     * @param identificador Identificador do projeto.
     */
    virtual void remover(const Identificador& identificador) = 0;
};

#endif
