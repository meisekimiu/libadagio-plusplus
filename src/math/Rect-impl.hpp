#ifndef GL_ADAGIO_RECT_IMPL_H
#define GL_ADAGIO_RECT_IMPL_H
namespace Adagio {
    template<typename T>
    Rect<T>::Rect() {
        position = Vector2<T>();
        size = Vector2<T>();
        correctNegativeSize();
    }

    template<typename T>
    Rect<T>::Rect(Vector2<T> position, Vector2<T> size) {
        this->position = position;
        this->size = size;
        correctNegativeSize();
    }

    template<typename T>
    Rect<T>::Rect(T x, T y, T w, T h) {
        position = Vector2<T>(x, y);
        size = Vector2<T>(w, h);
        correctNegativeSize();
    }

    template<typename T>
    template<typename U>
    Rect<T>::Rect(const Rect<U> &rect) {
        position = Vector2<T>(rect.position);
        size = Vector2<T>(rect.size);
        correctNegativeSize();
    }

    template<typename T>
    T Rect<T>::x() const {
        return position.x;
    }

    template<typename T>
    T Rect<T>::y() const {
        return position.y;
    }

    template<typename T>
    T Rect<T>::width() const {
        return size.x;
    }

    template<typename T>
    T Rect<T>::height() const {
        return size.y;
    }

    template<typename T>
    Vector2<T> Rect<T>::center() const {
        return position + (size / 2.0);
    }

    template<typename T>
    const std::array<Vector2<T>, 4> Rect<T>::corners() const {
        return std::array<Vector2<T>, 4>{
                Vector2<T>(position),
                Vector2<T>(position.x + size.x, position.y),
                Vector2<T>(position.x, position.y + size.y),
                Vector2<T>(position.x + size.x, position.y + size.y)
        };
    }

    template<typename T>
    bool Rect<T>::contains(Vector2<T> point) const {
        auto max = position + size;
        return point.x >= position.x && point.y >= position.y && point.x <= max.x && point.y <= max.y;
    }

    template<typename T>
    bool Rect<T>::contains(Rect<T> rect) const {
        auto corners = rect.corners();
        for (Vector2<T> corner: corners) {
            if (!contains(corner)) {
                return false;
            }
        }
        return true;
    }

    template<typename T>
    bool Rect<T>::intersects(Rect<T> rect) const {
        return position.x < rect.position.x + rect.size.x && position.x + size.x > rect.position.x &&
               position.y < rect.position.y + rect.size.y && position.y + size.y > rect.position.y;
    }

    template<typename T>
    inline std::string Rect<T>::to_string() const {
        std::stringstream sstream;
        sstream << *this;
        std::string str = sstream.str();
        return str;
    }

    template<typename T>
    inline std::ostream &operator<<(std::ostream &left, Rect<T> right) {
        return left << "Rect(" << right.position.x << "," << right.position.y << "," << right.size.x << ","
                    << right.size.y << ")";
    }

    template<typename T>
    void Rect<T>::correctNegativeSize() {
        correctNegativeValues(size.x, position.x);
        correctNegativeValues(size.y, position.y);
    }

    template<typename T>
    void Rect<T>::correctNegativeValues(T &sizeVal, T &positionVal) {
        if (sizeVal < 0) {
            positionVal += sizeVal;
            sizeVal = std::abs(sizeVal);
        }
    }
}
#endif //GL_ADAGIO_RECT_IMPL_H
