#pragma once

struct string;

class Shader{


    public:

    Shader(const string& vertexSrc,
    const string& fragmentSrc);

    ~Shader();

    void bind() const;

    private:

    unsigned int programID;


};