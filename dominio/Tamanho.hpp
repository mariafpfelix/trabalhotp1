/**
 * @file Tamanho.hpp
 * @brief Declaracao do dominio Tamanho.
 */

#ifndef TAMANHO_HPP
#define TAMANHO_HPP

#include <string>
#include <stdexcept>

/**
 * @brief Dominio que representa o tamanho (esforco) de um cartao
 *        de atividade.
 *
 * Valores validos: "GRANDE", "MEDIO" ou "PEQUENO".
 */
class Tamanho {
private:
    std::string valor; ///< Tamanho armazenado apos validacao.

public:
    /**
     * @brief Valida e armazena o tamanho informado.
     * @param novoTamanho Tamanho a ser validado.
     * @throw std::invalid_argument Se o valor nao for "GRANDE",
     *        "MEDIO" ou "PEQUENO".
     */
    void setTamanho(std::string novoTamanho) {

        if (novoTamanho != "GRANDE" &&
            novoTamanho != "MEDIO" &&
            novoTamanho != "PEQUENO") {

            throw std::invalid_argument("Tamanho invalido");
        }

        valor = novoTamanho;
    }

    /**
     * @brief Retorna o tamanho armazenado.
     * @return Tamanho valido previamente definido.
     */
    std::string getTamanho() const {
        return valor;
    }
};

#endif
