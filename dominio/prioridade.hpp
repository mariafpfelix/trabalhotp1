/**
 * @file prioridade.hpp
 * @brief Declaracao do dominio Prioridade.
 */

#ifndef PRIORIDADE_HPP
#define PRIORIDADE_HPP

#include <string>
#include <stdexcept>

using namespace std;

/**
 * @brief Dominio que representa a prioridade de um cartao de atividade.
 *
 * Valores validos: "ALTA", "MEDIA" ou "BAIXA".
 */
class Prioridade {
private:
    string valor; ///< Prioridade armazenada apos validacao.

public:
    /**
     * @brief Valida e armazena a prioridade informada.
     * @param novaPrioridade Prioridade a ser validada.
     * @throw std::invalid_argument Se o valor nao for "ALTA",
     *        "MEDIA" ou "BAIXA".
     */
    void setPrioridade(string novaPrioridade) {
        if (novaPrioridade != "ALTA" &&
            novaPrioridade != "MEDIA" &&
            novaPrioridade != "BAIXA") {

            throw invalid_argument("Prioridade invalida");
        }

        valor = novaPrioridade;
    }

    /**
     * @brief Retorna a prioridade armazenada.
     * @return Prioridade valida previamente definida.
     */
    string getPrioridade() const {
        return valor;
    }
};

#endif
