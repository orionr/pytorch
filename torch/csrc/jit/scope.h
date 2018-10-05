#pragma once
#include "torch/csrc/jit/interned_strings.h"
#include "torch/csrc/jit/assertions.h"
#include "c10/macros/Macros.h"

#include <memory>

namespace torch {
namespace jit {

// Scope is a node of a trie that represents the tree of nested scopes.
// Individual scopes are pushed and popped from Graph, which holds a
// pointer to the current scope. Each Node in Graph holds a pointer
// to the scope that was current when the node was created.
// The trie never needs to shrink, it only grows until it is disposed
// of when Graph is deallocated. Hence, pointers to scopes held by nodes
// will always be valid as long as Graph is alive.
struct Scope {
private:
  Scope* parent_;
  Symbol name_;
  std::vector<std::unique_ptr<Scope> > children_;
public:
  Scope() {
    name_ = Symbol::scope("");
    parent_ = nullptr;
  }
  Scope(Scope* parent, Symbol name) {
    name_ = name;
    parent_ = parent;
  }
  Scope* push(Symbol name) {
    children_.push_back(std::unique_ptr<Scope>(new Scope(this, name)));
    return children_.back().get();
  }
  Scope* parent() {
    if (parent_ == nullptr) {
      throw std::runtime_error("Cannot get parent from Scope with no parent");
    }
    return parent_;
  }
  bool isRoot() {
    return parent_ == nullptr;
  }
  Scope* getRoot() {
    Scope* current = this;
    while (current->parent_) {
      current = current->parent_;
    }
    return current;
  }
  Symbol name() {
    return name_;
  }
  std::string namesFromRoot(const std::string& separator="/") {
    // TODO: I think the answer is we shouldn't have used Symbol here
    std::string out = this->name_.toUnqualString();
    if (this->isRoot()) {
      return out;
    }
    Scope* parent = this->parent_;
    while (!parent->isRoot()) {
      // NOLINTNEXTLINE(performance-inefficient-string-concatenation)
      out = std::string(parent->name_.toUnqualString()) + separator + out;
      parent = parent->parent_;
    }
    return out;
  }

  C10_DISABLE_COPY_AND_ASSIGN(Scope);
};

} // namespace jit
} // namespace torch
