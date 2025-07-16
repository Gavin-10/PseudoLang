
#include "ASTGen.h"

ASTGen::ASTGen(const std::vector<unsigned char>& source, const std::vector<Token> tokens) 
		: source(source), tokens(tokens) {
};

std::vector<std::unique_ptr<Expr::Expr> > ASTGen::parse() {

		return std::move(this->AST);
}

std::unique_ptr<Expr::Expr> ASTGen::orr() {

}

std::unique_ptr<Expr::Expr> ASTGen::andd() {

}

std::unique_ptr<Expr::Expr> ASTGen::equality() {

}

std::unique_ptr<Expr::Expr> ASTGen::comparison() {

}

std::unique_ptr<Expr::Expr> ASTGen::term() {

}

std::unique_ptr<Expr::Expr> ASTGen::factor() {

}

std::unique_ptr<Expr::Expr> ASTGen::unary() {

}

std::unique_ptr<Expr::Expr> ASTGen::primary() {

}
