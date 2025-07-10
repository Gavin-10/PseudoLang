
#include "expr.h"

#include <stdexcept>

namespace Expr {

		//Expr
		template <class R>
		R Expr::dispatchToAccept(Visitor<R>& visitor) {
				switch (this->thisNode) {
				case ExprType::TERNARY:
						return visitor.visitTernaryExpr(this);

				case ExprType::BINARY:
						return visitor.visitBinaryExpr(this);

				case ExprType::GROUPING:
						return visitor.visitGroupingExpr(this);

				case ExprType::LITERAL:
						return visitor.visitLiteralExpr(this);

				case ExprType::LOGICAL:
						return visitor.visitLogicalExpr(this);

				case ExprType::UNARY:
						return visitor.visitUnaryExpr(this);

				default:
						throw std::invalid_argument("This AST Node does not contain a valid node type");
				}
		}

		//Ternary
		Ternary::Ternary(std::unique_ptr<Expr> expression, std::unique_ptr<Expr> left, std::unique_ptr<Expr> right)
				: expression(std::move(expression)), left(std::move(left)), right(std::move(right)) {

		}

		//Binary

		//Grouping

		//Literal

		//Logical

		//Unary
}