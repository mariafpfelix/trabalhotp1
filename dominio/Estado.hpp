/**
 * @file Estado.hpp
 * @brief Declaracao do dominio Estado.
 */

#ifndef ESTADO_HPP
#define ESTADO_HPP

#include <string>
#include <stdexcept>

/**
 * @brief Dominio que representa o estado de um cartao de atividade.
 *
 * Valores validos: "A FAZER", "FAZENDO" ou "FEITO".
 */
class Estado
{
private:
    std::string valor; ///< Estado armazenado apos validacao.

public:
    /**
     * @brief Valida e armazena o estado informado.
     * @param novoEstado Estado a ser validado.
     * @throw std::invalid_argument Se o valor nao for "A FAZER",
     *        "FAZENDO" ou "FEITO".
     */
    void setEstado(std::string novoEstado)
    {
        if (novoEstado != "A FAZER" &&
            novoEstado != "FAZENDO" &&
            novoEstado != "FEITO")
        {

            throw std::invalid_argument("Estado invalido");
        }

        valor = novoEstado;
    }

    /**
     * @brief Retorna o estado armazenado.
     * @return Estado valido previamente definido.
     */
    std::string getEstado() const
    {
        return valor;
    }
};

#endif
