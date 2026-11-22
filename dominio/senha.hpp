/**
 * @file senha.hpp
 * @brief Declaracao do dominio Senha.
 */

#ifndef SENHA_HPP
#define SENHA_HPP

#include <string>
#include <stdexcept>

using namespace std;

/**
 * @brief Dominio que representa a senha de acesso de uma pessoa.
 *
 * Regras de formato:
 * - Exatamente 5 caracteres.
 * - Apenas letras (A-Z, a-z) e digitos (0-9).
 * - Deve conter pelo menos uma letra e pelo menos um digito.
 */
class Senha {
private:
    string valor; ///< Senha armazenada apos validacao.

public:
    /**
     * @brief Valida e armazena a senha informada.
     * @param novaSenha Senha a ser validada.
     * @throw std::invalid_argument Se a senha nao tiver 5 caracteres,
     *        tiver caracteres invalidos ou nao misturar letras e digitos.
     */
    void setSenha(string novaSenha) {

        if (novaSenha.length() != 5) {
            throw invalid_argument("Senha invalida");
        }

        bool temLetra = false;
        bool temNumero = false;

        for (char c : novaSenha) {

            if ((c >= 'A' && c <= 'Z') ||
                (c >= 'a' && c <= 'z')) {
                temLetra = true;
            }
            else if (c >= '0' && c <= '9') {
                temNumero = true;
            }
            else {
                throw invalid_argument("Senha invalida");
            }
        }

        if (!temLetra || !temNumero) {
            throw invalid_argument("Senha invalida");
        }

        valor = novaSenha;
    }

    /**
     * @brief Retorna a senha armazenada.
     * @return Senha valida previamente definida.
     */
    string getSenha() const {
        return valor;
    }
};

#endif
