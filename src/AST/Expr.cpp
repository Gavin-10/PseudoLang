
#include "Expr.h"

#include <stdexcept>

namespace ExprOps {

		//Ternary
		Ternary::Ternary(std::unique_ptr<Expr> expression, std::unique_ptr<Expr> left, std::unique_ptr<Expr> right)
				: expression(std::move(expression)), left(std::move(left)), right(std::move(right)) {
		}

		void Ternary::accept(Visitor& visitor) {
			visitor.visitTernaryExpr(*this);
		}

		//Binary
		Binary::Binary(std::unique_ptr<Expr> left, Token operatorr, std::unique_ptr<Expr> right)
				: left(std::move(left)), operatorr(operatorr), right(std::move(right)) {
		}

		void Binary::accept(Visitor& visitor) {
			visitor.visitBinaryExpr(*this);
		}

		//Grouping
		Grouping::Grouping(std::unique_ptr<Expr> expression)
				: expression(std::move(expression)) {
		}

		void Grouping::accept(Visitor& visitor) {
			visitor.visitGroupingExpr(*this);
		}

		//Literal
		Literal::Literal(Value value, int line) : value(value), line(line) {
		}

		void Literal::accept(Visitor& visitor) {
			visitor.visitLiteralExpr(*this);
		}

		//Logical
		Logical::Logical(std::unique_ptr<Expr> left, Token operatorr, std::unique_ptr<Expr> right)
				: left(std::move(left)), operatorr(operatorr), right(std::move(right)) {
		}

		void Logical::accept(Visitor& visitor) {
			visitor.visitLogicalExpr(*this);
		}

		//Unary
		Unary::Unary(Token operatorr, std::unique_ptr<Expr> right)
				: operatorr(operatorr), right(std::move(right)) {
		}

		void Unary::accept(Visitor& visitor) {
			visitor.visitUnaryExpr(*this);
		}
}