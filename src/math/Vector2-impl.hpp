namespace Adagio {
    template<typename T>
    Vector2<T>::Vector2() {
        this->x = 0;
        this->y = 0;
    }

    template<typename T>
    Vector2<T>::Vector2(T x, T y) {
        this->x = x;
        this->y = y;
    }

    template<typename T>
    template<typename U>
    Vector2<T>::Vector2(const Vector2<U> &v) {
        this->x = static_cast<T>(v.x);
        this->y = static_cast<T>(v.y);
    }

    template<typename T>
    double Vector2<T>::magnitude() const {
        return sqrt(x * x + y * y);
    }

    template<typename T>
    double Vector2<T>::magnitudeSquared() const {
        return x * x + y * y;
    }

    template<typename T>
    std::string Vector2<T>::to_string() const {
        std::stringstream sstream;
        sstream << *this;
        std::string str = sstream.str();
        return str;
    }

    template<typename T>
    Vector2<T> Vector2<T>::normalized() const {
        double length = magnitude();
        return Vector2<T>{x / length, y / length};
    }

    template<typename T>
    Vector2<T> Vector2<T>::floor() const {
        return Vector2<T>{std::floor(x), std::floor(y)};
    }

    template<typename T>
    void Vector2<T>::clamp(const Vector2<T> &lower, const Vector2<T> &upper) {
        x = std::max(std::min(upper.x, x), lower.x);
        y = std::max(std::min(upper.y, y), lower.y);
    }

    template<typename T>
    Vector2<T> operator+(const Vector2<T> &left, Vector2<T> right) {
        return Vector2<T>{left.x + right.x, left.y + right.y};
    }

    template<typename T>
    Vector2<T> operator-(const Vector2<T> &left, Vector2<T> right) {
        return Vector2<T>{left.x - right.x, left.y - right.y};
    }

    template<typename T>
    Vector2<T> operator+=(Vector2<T> &left, Vector2<T> right) {
        left.x += right.x;
        left.y += right.y;

        return left;
    }

    template<typename T>
    Vector2<T> operator-=(Vector2<T> &left, Vector2<T> right) {
        left.x -= right.x;
        left.y -= right.y;

        return left;
    }

    template<typename T>
    Vector2<T> operator*(const Vector2<T> &left, T right) {
        return Vector2<T>{left.x * right, left.y * right};
    }

    template<typename T>
    Vector2<T> operator*(T left, const Vector2<T> &right) {
        return Vector2<T>{left * right.x, left * right.y};
    }

    template<typename T>
    Vector2<T> operator/(const Vector2<T> &left, T right) {
        return Vector2<T>{left.x / right, left.y / right};
    }

    template<typename T>
    Vector2<T> operator/(T left, const Vector2<T> &right) {
        return Vector2<T>{left / right.x, left / right.y};
    }

    template<typename T>
    bool operator==(const Vector2<T> &left, const Vector2<T> &right) {
        return left.x == right.x && left.y == right.y;
    }

    template<typename T>
    bool operator!=(const Vector2<T> &left, const Vector2<T> &right) {
        return left.x != right.x && left.y != right.y;
    }

    template<typename T>
    inline std::ostream &operator<<(std::ostream &left, const Vector2<T> &right) {
        return left << "Vector2(" << right.x << "," << right.y << ")";
    }
} // namespace Adagio
