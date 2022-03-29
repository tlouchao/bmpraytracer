#ifndef COLOR_H
#define COLOR_H

class Color {
    public:
        virtual unsigned short getDepth() = 0;
        virtual unsigned char* getArr() = 0;
};

class ColorRGB : public Color {
    protected:
        unsigned char R, G, B;
    public:
        ColorRGB (const unsigned char R, const unsigned char G, const unsigned char B);
        unsigned char getR();
        unsigned char getG();
        unsigned char getB();
        void setR(const unsigned char R_in);
        void setG(const unsigned char G_in);
        void setB(const unsigned char B_in);
        unsigned short getDepth() override;
        unsigned char* getArr() override;
        friend bool operator==(ColorRGB& c1, ColorRGB& c2);
};

class ColorRGBA : public ColorRGB {
    protected:
        unsigned char A;
    public:
        ColorRGBA (const unsigned char R, const unsigned char G, const unsigned char B, const unsigned char A);
        unsigned char getA();
        void setA(const unsigned char A_in);
        unsigned short getDepth() override;
        unsigned char* getArr() override;
        friend bool operator==(ColorRGBA& c1, ColorRGBA& c2);
};


#endif