#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sunglasses/Sunglasses.hpp>

using namespace sunglasses;

typedef Node<void> N;

struct NodeTest : ::testing::Test {
	// Top level
	Node<void> *root;

	Node<void> *A, *B;
	
	Node<void> *AA, *AB, *BA;
	
	Node<void> *AAA, *AAB, *BAA, *BAB, *BAC, *BAD;

	NodeTest() {
		root = new N();
		
		A = new N(root);
		B = new N(root);
		
		AA = new N(A);
		AB = new N(A);
		BA = new N(B);
		
		AAA = new N(AA);
		AAB = new N(AA);
		BAA = new N(BA);
		BAB = new N(BA);
		BAC = new N(BA);
		BAD = new N(BA);
	}
	
	~NodeTest() {
		delete root;
	}
};

bool isChild(N *parent, N *child) {
		return (std::find(parent->getChildren().begin(), parent->getChildren().end(),
				child) != parent->getChildren().end());
}

TEST_F(NodeTest, Structure) {
	EXPECT_TRUE(isChild(root, A));
	EXPECT_TRUE(isChild(root, B));
	EXPECT_FALSE(isChild(root, AB));
	
	EXPECT_EQ(A->getRight(), B);
	EXPECT_EQ(A->getParent(), root);
	EXPECT_EQ(B->getLeft(), A);
	EXPECT_EQ(B->getParent(), root);
	
	
	EXPECT_EQ(BAA->getRight(), BAB);
	EXPECT_EQ(BAB->getLeft(), BAA);
	EXPECT_EQ(BAB->getRight(), BAC);
	EXPECT_EQ(BAC->getLeft(), BAB);
	EXPECT_EQ(BAC->getRight(), BAD);
	EXPECT_EQ(BAD->getLeft(), BAC);
	
	BA->removeChild(BAC);
	
	EXPECT_FALSE(isChild(BA, BAC));
	EXPECT_EQ(BAC->getParent(), nullptr);
	EXPECT_EQ(BAC->getLeft(), nullptr);
	EXPECT_EQ(BAC->getRight(), nullptr);
	EXPECT_EQ(BAB->getRight(), BAD);
	EXPECT_EQ(BAD->getLeft(), BAB);
	
	AB->setParent(nullptr);
	
	EXPECT_FALSE(isChild(A, AB));
	EXPECT_EQ(AB->getParent(), nullptr);
	EXPECT_EQ(AB->getLeft(), nullptr);
	EXPECT_EQ(AB->getRight(), nullptr);
	EXPECT_EQ(AA->getRight(), nullptr);
	
	
	AAA->setParent(nullptr);
	
	EXPECT_FALSE(isChild(AA, AAA));
	EXPECT_EQ(AAA->getParent(), nullptr);
	EXPECT_EQ(AAA->getLeft(), nullptr);
	EXPECT_EQ(AAA->getRight(), nullptr);
	EXPECT_EQ(AAB->getLeft(), nullptr);
}