/**
 * @file ServicoQuadros.hpp
 * @brief Implementacao do servico de quadros.
 */

#ifndef SERVICOQUADROS_HPP
#define SERVICOQUADROS_HPP

#include "../interfaces/IQuadros.hpp"
#include "../containers/Quadros.hpp"

/**
 * @brief Implementa os servicos relacionados aos quadros.
 */
class ServicoQuadros : public IQuadros
{

private:
    /**
     * @brief Referencia ao container responsavel pela persistencia.
     */
    Quadros &repositorio;

public:
    /**
     * @brief Inicializa o servico com o container de quadros.
     * @param quadros Referencia ao container.
     */
    explicit ServicoQuadros(Quadros &quadros)
        : repositorio(quadros)
    {
    }

    /**
     * @brief Cadastra um quadro.
     * @param quadro Entidade Quadro com os dados a serem gravados.
     */
    void cadastrar(const Quadro &quadro) override
    {
        repositorio.inserir(quadro);
    }

    /**
     * @brief Consulta um quadro pelo identificador.
     * @param identificador Identificador do quadro.
     * @return Entidade encontrada.
     */
    Quadro consultar(const Identificador &identificador) override
    {
        return repositorio.consultar(identificador);
    }

    /**
     * @brief Lista todos os quadros.
     * @return Vetor com os registros encontrados.
     */
    std::vector<Quadro> listar() override
    {
        return repositorio.listar();
    }

    /**
     * @brief Atualiza um quadro.
     * @param quadro Entidade Quadro com os dados a serem gravados.
     */
    void atualizar(const Quadro &quadro) override
    {
        repositorio.atualizar(quadro);
    }

    /**
     * @brief Remove um quadro pelo identificador.
     * @param identificador Identificador do quadro.
     */
    void remover(const Identificador &identificador) override
    {
        repositorio.remover(identificador);
    }
};

#endif
