/**
 * @file papel.hpp
 * @brief Declaracao do dominio Papel.
 */

#ifndef PAPEL_HPP
#define PAPEL_HPP

#include <string>
#include <stdexcept>

using namespace std;

/**
 * @brief Dominio que representa o papel de uma pessoa no sistema.
 *
 * Valores validos: "GESTOR" ou "DESENVOLVEDOR".
 * O papel determina quais operacoes a pessoa pode realizar.
 */
class Papel {
private:
    string valor; ///< Papel armazenado apos validacao.

public:
    /**
     * @brief Valida e armazena o papel informado.
     * @param novoPapel Papel a ser validado.
     * @throw std::invalid_argument Se o valor nao for "GESTOR"
     *        nem "DESENVOLVEDOR".
     */
    void setPapel(string novoPapel) {
        if (novoPapel != "GESTOR" &&
            novoPapel != "DESENVOLVEDOR") {

            throw invalid_argument("Papel invalido");
        }

        valor = novoPapel;
    }

    /**
     * @brief Retorna o papel armazenado.
     * @return Papel valido previamente definido.
     */
    string getPapel() const {
        return valor;
    }
};

#endif
