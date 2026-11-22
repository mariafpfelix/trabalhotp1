/**
 * @file nome.hpp
 * @brief Declaracao do dominio Nome.
 */

#ifndef NOME_HPP
#define NOME_HPP

#include <string>
#include <stdexcept>

/**
 * @brief Dominio que representa o nome de pessoas, projetos,
 *        quadros e cartoes.
 *
 * Regras de formato:
 * - Entre 1 e 15 caracteres.
 * - Apenas letras (A-Z, a-z) e espacos.
 * - Nao pode comecar nem terminar com espaco.
 * - Todo espaco deve ser seguido por uma letra.
 */
class Nome {
private:
    std::string valor; ///< Nome armazenado apos validacao.

public:
    /**
     * @brief Valida e armazena o nome informado.
     * @param novoNome Nome a ser validado.
     * @throw std::invalid_argument Se o nome violar alguma das
     *        regras de formato.
     */
    void setNome(std::string novoNome) {

        if (novoNome.empty() || novoNome.length() > 15) {
            throw std::invalid_argument("Nome invalido");
        }

        // Verifica se o primeiro ou ultimo caractere e espaco
        if (novoNome[0] == ' ' ||
            novoNome[novoNome.length() - 1] == ' ') {

            throw std::invalid_argument("Nome invalido");
        }

        for (size_t i = 0; i < novoNome.length(); i++) {

            char c = novoNome[i];

            bool letra = (c >= 'A' && c <= 'Z') ||
                         (c >= 'a' && c <= 'z');

            if (!letra && c != ' ') {
                throw std::invalid_argument("Nome invalido");
            }

            // Todo espaco deve ser seguido por uma letra
            if (c == ' ') {

                char proximo = novoNome[i + 1];

                bool proximaLetra =
                    (proximo >= 'A' && proximo <= 'Z') ||
                    (proximo >= 'a' && proximo <= 'z');

                if (!proximaLetra) {
                    throw std::invalid_argument("Nome invalido");
                }
            }
        }

        valor = novoNome;
    }

    /**
     * @brief Retorna o nome armazenado.
     * @return Nome valido previamente definido.
     */
    std::string getNome() const {
        return valor;
    }
};

#endif
