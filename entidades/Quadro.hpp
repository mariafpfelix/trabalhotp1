/**
 * @file Quadro.hpp
 * @brief Declaracao da entidade Quadro.
 */

#ifndef QUADRO_HPP
#define QUADRO_HPP

#include "../dominio/identificador.hpp"
#include "../dominio/nome.hpp"
#include "../dominio/Limite.hpp"
#include <stdexcept>

/**
 * @class Quadro
 * @brief Representa um quadro Kanban pertencente a um projeto.
 *
 * Cada quadro possui um identificador único, um nome
 * e um limite máximo de atividades simultâneas na coluna FAZENDO.
 */
class Quadro {
private:

    /**
     * @brief Identificador unico do quadro.
     */
    Identificador identificador;

    /**
     * @brief Nome do quadro.
     */
    Nome nome;

    /**
     * @brief Limite WIP de cartoes simultaneos em FAZENDO.
     */
    Limite limite;

    /**
     * @brief Identificador do projeto ao qual o quadro pertence.
     */
    Identificador projeto;

    /**
     * @brief Indica se o identificador ja foi definido.
     */
    bool identificadorDefinido = false;

public:

    /**
     * @brief Define o identificador do quadro.
     * @param novoIdentificador Identificador validado.
     * @throw std::invalid_argument Caso já tenha sido definido.
     */
    void setIdentificador(const Identificador& novoIdentificador) {

        if (identificadorDefinido) {
            throw std::invalid_argument(
                "O identificador nao pode ser alterado."
            );
        }

        identificador = novoIdentificador;
        identificadorDefinido = true;
    }

    /**
     * @brief Retorna o identificador do quadro.
     * @return Referencia constante para o identificador.
     */
    const Identificador& getIdentificador() const {
        return identificador;
    }

    /**
     * @brief Define o nome do quadro.
     * @param novoNome Nome validado do quadro.
     */
    void setNome(const Nome& novoNome) {
        nome = novoNome;
    }

    /**
     * @brief Retorna o nome do quadro.
     * @return Referencia constante para o nome.
     */
    const Nome& getNome() const {
        return nome;
    }

    /**
     * @brief Define o limite de atividades simultâneas.
     * @param novoLimite Limite WIP validado.
     */
    void setLimite(const Limite& novoLimite) {
        limite = novoLimite;
    }

    /**
     * @brief Retorna o limite de atividades simultâneas.
     * @return Referencia constante para o limite WIP.
     */
    const Limite& getLimite() const {
        return limite;
    }

    /**
     * @brief Define o projeto ao qual o quadro pertence.
     * @param novoProjeto Identificador do projeto associado.
     */
    void setProjeto(const Identificador& novoProjeto) {
        projeto = novoProjeto;
    }

    /**
     * @brief Retorna o projeto ao qual o quadro pertence.
     * @return Referencia constante para o identificador do projeto.
     */
    const Identificador& getProjeto() const {
        return projeto;
    }
};

#endif
