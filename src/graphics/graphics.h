#ifndef GRAPHICS_H
#define GRAPHICS_H
class Graphics {
    public:
        enum ReturnType 
        {
            OK = 0,
            ERROR_JSON_FILENAME,
            ERROR_JSON_LOAD
        };
        virtual void Draw(u_int x, u_int y) = 0;
};


#endif