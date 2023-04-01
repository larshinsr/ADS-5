#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template <typename T, int size>
class TStack {
 private:
     int top;
     T arr[size] = {0};

 public:
     TStack() : top(-1) {}
     bool isFull() const { return size == top - 1; }
     bool isEmpty() { return -1 == top; }
     void push(T value) {
         if (!isFull()) {
             arr[++top] = value;
         }
     }
     T get() const { return arr[top]; }
     T pop() { return arr[top--]; }
};
#endif  // INCLUDE_TSTACK_H_
