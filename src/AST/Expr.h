
#pragma once

#include <variant>
#include <memory>

#include "Token.h"
#include "Object.h"

namespace Expr {

		typedef std::variant<bool, double, Obj*, nullptr_t> Value;

		template <class T>
		struct Visitor;

		struct Expr {
				enum class ExprType {
						DEFAULT, TERNARY, BINARY, GROUPING, LITERAL, LOGICAL, UNARY,
				};

				template <class R>
				R dispatchToAccept(Visitor<R>&);

		protected:
				const ExprType thisNode = ExprType::DEFAULT;
		};

		struct Ternary : Expr {
				Ternary(std::unique_ptr<Expr>, std::unique_ptr<Expr>, std::unique_ptr<Expr>);

				std::unique_ptr<Expr> expression;
				std::unique_ptr<Expr> left;
				std::unique_ptr<Expr> right;

		private:
				const ExprType thisNode = ExprType::TERNARY;
		};

		struct Binary : Expr {
				Binary(std::unique_ptr<Expr>, Token, std::unique_ptr<Expr>);

				std::unique_ptr<Expr> left;
				const Token operatorr;
				std::unique_ptr<Expr> right;

		private:
				const ExprType thisNode = ExprType::BINARY;
		};

		struct Grouping : Expr {
				Grouping(std::unique_ptr<Expr>);

				std::unique_ptr<Expr> expression;

		private:
				const ExprType thisNode = ExprType::GROUPING;
		};

		struct Literal : Expr {
				Literal(Value value);

				const Value value;

		private:
				const ExprType thisNode = ExprType::LITERAL;
		};

		struct Logical : Expr {
				Logical(std::unique_ptr<Expr>, Token, std::unique_ptr<Expr>);

				std::unique_ptr<Expr> left;
				const Token operatorr;
				std::unique_ptr<Expr> right;

		private:
				const ExprType thisNode = ExprType::LOGICAL;
		};

		struct Unary : Expr {
				Unary(Token, std::unique_ptr<Expr>);

				const Token operatorr;
				std::unique_ptr<Expr> right;

		private:
				const ExprType thisNode = ExprType::UNARY;
		};

		template <class T>
		struct Visitor {
				T visitTernaryExpr(Ternary& expr) =0;
				T visitBinaryExpr(Binary& expr) =0;
				T visitGroupingExpr(Grouping& expr) =0;
				T visitLiteralExpr(Literal& expr) =0;
				T visitLogicalExpr(Logical& expr) =0;
				T visitUnaryExpr(Unary& expr) =0;
		};
}