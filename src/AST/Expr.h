
#pragma once

#include <variant>
#include <memory>

#include "Token.h"
#include "Object.h"
#include "Value.h"

using namespace ValueOps;

namespace ExprOps {

		struct Visitor;

		struct Expr {
			virtual ~Expr() = default;

			virtual void accept(Visitor&) =0;

		};

		struct Ternary : Expr {
			Ternary(std::unique_ptr<Expr>, std::unique_ptr<Expr>, std::unique_ptr<Expr>);

			void accept(Visitor&) override;

			const std::unique_ptr<Expr> expression;
			const std::unique_ptr<Expr> left;
			const std::unique_ptr<Expr> right;
		};

		struct Binary : Expr {
			Binary(std::unique_ptr<Expr>, Token, std::unique_ptr<Expr>);

			void accept(Visitor&) override;

			const std::unique_ptr<Expr> left;
			const Token operatorr;
			const std::unique_ptr<Expr> right;
		};

		struct Grouping : Expr {
			Grouping(std::unique_ptr<Expr>);

			void accept(Visitor&) override;

			const std::unique_ptr<Expr> expression;
		};

		struct Literal : Expr {
			Literal(Value, int);

			void accept(Visitor&) override;

			const Value value;
			const int line;
		};

		struct Logical : Expr {
			Logical(std::unique_ptr<Expr>, Token, std::unique_ptr<Expr>);

			void accept(Visitor&) override;

			const std::unique_ptr<Expr> left;
			const Token operatorr;
			const std::unique_ptr<Expr> right;
		};

		struct Unary : Expr {
			Unary(Token, std::unique_ptr<Expr>);

			void accept(Visitor&) override;

			const Token operatorr;
			const std::unique_ptr<Expr> right;
		};

		struct Visitor {
			virtual ~Visitor() = default;

			Value result = nullptr;

			virtual void visitTernaryExpr(const Ternary& expr) =0;
			virtual void visitBinaryExpr(const Binary& expr) =0;
			virtual void visitGroupingExpr(const Grouping& expr) =0;
			virtual void visitLiteralExpr(const Literal& expr) =0;
			virtual void visitLogicalExpr(const Logical& expr) =0;
			virtual void visitUnaryExpr(const Unary& expr) =0;
		};
}