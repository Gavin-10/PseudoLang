
#include "ASTGen.h"

ASTGen::ASTGen(const std::vector<unsigned char>& source, const std::vector<Token> tokens) 
		: source(source), tokens(tokens) {
};

std::vector<std::unique_ptr<Expr::Expr> > ASTGen::parse() {

		return std::move(this->AST);
}