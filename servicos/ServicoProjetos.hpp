/**
 * @file ServicoProjetos.hpp
 * @brief Implementacao do servico de projetos.
 */

#ifndef SERVICOPROJETOS_HPP
#define SERVICOPROJETOS_HPP

#include "../interfaces/IProjetos.hpp"
#include "../containers/Projetos.hpp"

/**
 * @brief Implementa os servicos relacionados aos projetos.
 */
class ServicoProjetos : public IProjetos
{

private:
    /**
     * @brief Referencia ao container responsavel pela persistencia.
     */
    Projetos &repositorio;

public:
    /**
     * @brief Inicializa o servico com o container de projetos.
     * @param projetos Referencia ao container.
     */
    explicit ServicoProjetos(Projetos &projetos)
        : repositorio(projetos)
    {
    }

    /**
     * @brief Cadastra um projeto.
     * @param projeto Entidade Projeto com os dados a serem gravados.
     */
    void cadastrar(const Projeto &projeto) override
    {
        repositorio.inserir(projeto);
    }

    /**
     * @brief Consulta um projeto pelo identificador.
     * @param identificador Identificador do projeto.
     * @return Entidade encontrada.
     */
    Projeto consultar(const Identificador &identificador) override
    {
        return repositorio.consultar(identificador);
    }

    /**
     * @brief Lista todos os projetos.
     * @return Vetor com os registros encontrados.
     */
    std::vector<Projeto> listar() override
    {
        return repositorio.listar();
    }

    /**
     * @brief Atualiza um projeto.
     * @param projeto Entidade Projeto com os dados a serem gravados.
     */
    void atualizar(const Projeto &projeto) override
    {
        repositorio.atualizar(projeto);
    }

    /**
     * @brief Remove um projeto pelo identificador.
     * @param identificador Identificador do projeto.
     */
    void remover(const Identificador &identificador) override
    {
        repositorio.remover(identificador);
    }
};

#endif
