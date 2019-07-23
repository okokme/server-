class Noncopyable {
public:
    Noncopyable() { }
    ~Noncopyable() { }
private:
    Noncopyable(const Noncopyable&);
    const Noncopyable& operator=(const Noncopyable&);
};