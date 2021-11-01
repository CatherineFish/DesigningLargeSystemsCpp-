#pragma once

#include <memory>

namespace bintree {
    template <typename T>
    struct TNode : std::enable_shared_from_this<TNode<T>> {
        // указатель на родителя теперь weak_ptr, чтобы не было циклических зависмостей с shared_ptr
        using weakPtr = std::weak_ptr<TNode<T>>; 
        using TNodePtr = std::shared_ptr<TNode<T>>;
        using TNodeConstPtr = std::shared_ptr<const TNode<T>>;

        bool hasLeft() const {
            return bool(left);
        }

        bool hasRight() const {
            return bool(right);
        }

        bool hasParent() const {
            // т.к. теперь это weak_ptr
            return bool(parent.expired());
        }

        T& getValue() {
            return value;
        }

        const T& getValue() const {
            return value;
        }

        TNodePtr getLeft() {
            return left;
        }

        TNodeConstPtr getLeft() const {
            return left;
        }

        TNodePtr getRight() {
            return right;
        }

        TNodeConstPtr getRight() const {
            return right;
        }

        TNodePtr getParent() {
            // т.к. теперь это weak_ptr
            return parent.lock();
        }

        TNodeConstPtr getParent() const {
            // т.к. теперь это weak_ptr
            return parent.lock();
        }

        static TNodePtr createLeaf(T v) {
            // make_shared не мог обращаться к конструктору, т.к. он (конструктор) приватный
            // теперь тут явный вызов конструктора
            return TNodePtr(new TNode(v));
        }

        static TNodePtr fork(T v, TNode * left, TNode * right) {
            // аналогично createLeaf
            TNodePtr ptr = TNodePtr(new TNode(v, left, right));
            setParent(ptr->getRight(), ptr);
            setParent(ptr->getLeft(), ptr);
            return ptr;
        }

        TNodePtr replaceLeft(TNodePtr l) {
            // получение shared_ptr на себя без повторного создания (два указателя, которые не знают друг о друге, на один объект)
            setParent(l, this->shared_from_this());
            setParent(left, nullptr);
            std::swap(l, left);
            return l;
        }

        TNodePtr replaceRight(TNodePtr r) {
            // аналогично replaceLeft
            setParent(r, this->shared_from_this()); //new
            setParent(right, nullptr);
            std::swap(r, right);
            return r;
        }

        TNodePtr replaceRightWithLeaf(T v) {
            return replaceRight(createLeaf(v));
        }

        TNodePtr replaceLeftWithLeaf(T v) {
            return replaceLeft(createLeaf(v));
        }

        TNodePtr removeLeft() {
            return replaceLeft(nullptr);
        }
        TNodePtr removeRight() {
            return replaceRight(nullptr);
        }

    private:
        T value;
        TNodePtr left = nullptr;
        TNodePtr right = nullptr;
        // указатель на родителя теперь weak_ptr
        weakPtr parent;

        TNode(T v)
            : value(v)
        {
        }


        TNode(T v, TNode* left, TNode* right)
            : value(v)
            , left(left ? left->shared_from_this() : TNodePtr(nullptr))
            , right(right ? right->shared_from_this() : TNodePtr(nullptr))
        {
        }

        static void setParent(TNodePtr node, TNodePtr parent) {
            if (node)
                node->parent = parent;
        }
    };
}
