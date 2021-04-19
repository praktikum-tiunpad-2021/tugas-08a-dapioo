#pragma once

namespace strukdat {

namespace priority_queue {

/**
 * @brief Implementasi struct untuk elemen, harus ada isi dan prioritas elemen.
 */
template <typename T>
struct Element {
  T info;
  int prior;
  Element *next;
};

template <typename T>
using ElementPtr = Element<T> *;

/**
 * @brief implemetasi struct untuk queue.
 */
template <typename T>
struct Queue {
  ElementPtr<T> head;
  ElementPtr<T> last;
};

/**
 * @brief membuat queue baru
 *
 * @return  queue kosong
 */
template <typename T>
Queue<T> new_queue() {
  Queue<T> q;
  q.head = nullptr;
  q.last = nullptr;
  return q;
}

/**
 * @brief memasukan data sesuai priority elemen.
 *
 * @param q         queue yang dipakai.
 * @param value     isi dari elemen.
 * @param priority  prioritas elemen yang menentukan urutan.
 */
template <typename T>
void enqueue(Queue<T> &q, const T &value, int prior) {
  ElementPtr<T> newElement = new Element<T>;
  newElement->info = value;
  newElement->prior = prior;
  newElement->next = nullptr;

  ElementPtr<T> prev = nullptr;
  if (q.head == nullptr && q.last == nullptr) {
    q.head = newElement;
    q.last = newElement;
  } else {
    ElementPtr<T> pHelp = q.head;
    while (newElement->prior <= pHelp->prior) {
      if (pHelp->next == nullptr)
        break;
      prev = pHelp;
      pHelp = pHelp->next;
    }

    if (pHelp == q.head && newElement->prior > pHelp->prior) {
      newElement->next = pHelp;
      q.head = newElement;
    } else if (pHelp == q.last && newElement->prior < pHelp->prior) {
      pHelp->next = newElement;
      q.last = newElement;
    } else {
      prev->next = newElement;
      newElement->next = pHelp;
    }
  }
}

/**
 * @brief mengembalikan isi dari elemen head.
 *
 * @param q   queue yang dipakai.
 * @return    isi dari elemen head.
 */
template <typename T>
T top(const Queue<T> &q) {
  return q.head->info;
}

/**
 * @brief menghapus elemen head queue (First in first out).
 *
 * @param q   queue yang dipakai.
 */
template <typename T>
void dequeue(Queue<T> &q) {
  ElementPtr<T> target;
  if (q.head == nullptr && q.last == nullptr) {
    target = nullptr;
  } else if (q.head->next == nullptr) {
    target = q.head;
    q.head = nullptr;
    q.last = nullptr;
  } else {
    target = q.head;
    q.head = q.head->next;
    target->next = nullptr;
  }
}

}  // namespace priority_queue

}  // namespace strukdat
