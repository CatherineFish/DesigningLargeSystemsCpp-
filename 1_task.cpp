class ComplexNumber {
	
    private:
        int real;
    int img;
    public:
        constexpr ComplexNumber(int re = 0, int im = 0): real(re), img(im) {}

    constexpr bool operator == (const ComplexNumber & other) const {
        return (real == other.real && img == other.img) ? true : false;
    }

    constexpr void SetRe(int re) {
        real = re;
        return;
    }

    constexpr void SetIm(int im) {
        img = im;
        return;
    }

    constexpr int GetRe() const {
        return real;
    }

    constexpr int GetIm() const {
        return img;
    }
};

constexpr ComplexNumber Conjugate(const ComplexNumber & x) {
    ComplexNumber res;
    res.SetRe(x.GetRe());
    res.SetIm(-x.GetIm());
    return res;
}

int main() {
    constexpr ComplexNumber a(1, 2);
    constexpr ComplexNumber b(1, -2);
    constexpr auto c = Conjugate(a);
    static_assert(b == c, "failed");
}