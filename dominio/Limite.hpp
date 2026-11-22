/**
 * @file Limite.hpp
 * @brief Declaracao do dominio Limite.
 */

#ifndef LIMITE_HPP
#define LIMITE_HPP

#include <stdexcept>

/**
 * @brief Dominio que representa o limite WIP (Work In Progress)
 *        de um quadro.
 *
 * Valores validos: inteiros de 1 a 25.
 */
class Limite {
private:
    int valor; ///< Limite armazenado apos validacao.

public:
    /**
     * @brief Valida e armazena o limite informado.
     * @param novoValor Limite de atividades simultaneas.
     * @throw std::invalid_argument Se o valor estiver fora do
     *        intervalo de 1 a 25.
     */
    void setValor(int novoValor) {
        if (novoValor < 1 || novoValor > 25) {
            throw std::invalid_argument(
                "O limite WIP deve estar entre 1 e 25."
            );
        }

        valor = novoValor;
    }

    /**
     * @brief Retorna o limite armazenado.
     * @return Limite WIP valido previamente definido.
     */
    int getValor() const {
        return valor;
    }
};

#endif
