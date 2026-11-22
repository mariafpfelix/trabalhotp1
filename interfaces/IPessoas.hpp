/**
 * @file IPessoas.hpp
 * @brief Interface do servico de pessoas.
 */

#ifndef IPESSOAS_HPP
#define IPESSOAS_HPP

#include "../entidades/Pessoa.hpp"
#include <vector>

/**
 * @class IPessoas
 * @brief Interface para operacoes relacionadas a pessoas.
 */
class IPessoas
{
public:
    /**
     * @brief Destrutor virtual.
     */
    virtual ~IPessoas() = default;

    /**
     * @brief Cadastra uma pessoa.
     * @param pessoa Pessoa a ser cadastrada.
     */
    virtual void cadastrar(const Pessoa &pessoa) = 0;

    /**
     * @brief Consulta uma pessoa pelo email.
     * @param email Email da pessoa.
     * @return Pessoa encontrada.
     */
    virtual Pessoa consultar(const Email &email) = 0;

    /**
     * @brief Lista todas as pessoas cadastradas.
     * @return Vetor com as pessoas cadastradas.
     */
    virtual std::vector<Pessoa> listar() = 0;

    /**
     * @brief Atualiza os dados de uma pessoa.
     * @param pessoa Pessoa com os dados atualizados.
     */
    virtual void atualizar(const Pessoa &pessoa) = 0;

    /**
     * @brief Remove uma pessoa pelo email.
     * @param email Email da pessoa.
     */
    virtual void remover(const Email &email) = 0;
};

#endif
