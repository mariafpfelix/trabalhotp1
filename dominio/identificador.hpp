/**
 * @file identificador.hpp
 * @brief Declaracao do dominio Identificador.
 */

#ifndef IDENTIFICADOR_HPP
#define IDENTIFICADOR_HPP

#include <string>
#include <stdexcept>

/**
 * @brief Dominio que representa o identificador de projetos,
 *        quadros e cartoes.
 *
 * Formato: exatamente 6 caracteres, sendo 3 letras (A-Z ou a-z)
 * seguidas de 3 digitos (0-9). Exemplo: "PRJ001".
 */
class Identificador {
private:
    std::string valor; ///< Identificador armazenado apos validacao.

public:
    /**
     * @brief Valida e armazena o identificador informado.
     * @param novoIdentificador Identificador a ser validado.
     * @throw std::invalid_argument Se nao tiver 6 caracteres ou nao
     *        seguir o formato LLLDDD.
     */
    void setIdentificador(std::string novoIdentificador) {

        if (novoIdentificador.length() != 6) {
            throw std::invalid_argument("Identificador invalido");
        }

        // Os tres primeiros caracteres devem ser letras
        for (int i = 0; i < 3; i++) {
            char c = novoIdentificador[i];

            if (!((c >= 'A' && c <= 'Z') ||
                  (c >= 'a' && c <= 'z'))) {
                throw std::invalid_argument("Identificador invalido");
            }
        }

        // Os tres ultimos caracteres devem ser digitos
        for (int i = 3; i < 6; i++) {
            char c = novoIdentificador[i];

            if (c < '0' || c > '9') {
                throw std::invalid_argument("Identificador invalido");
            }
        }

        valor = novoIdentificador;

    }

    /**
     * @brief Retorna o identificador armazenado.
     * @return Identificador valido previamente definido.
     */
    std::string getIdentificador() const {
        return valor;
    }

};

#endif
