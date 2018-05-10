#include "include/Matrix22.h"

Matrix22 Matrix22Create(){
    Matrix22 ret;

    //make it identity
    Matrix22SetIdentity(&ret);

    return ret;
}

Matrix22 Matrix22MultScalar(Matrix22* matrix, float scalar){
    Matrix22 ret;

    ret.lh = matrix->lh * scalar;
    ret.rh = matrix->rh * scalar;
    ret.ll = matrix->ll * scalar;
    ret.rl = matrix->rl * scalar;

    return ret;
}

void Matrix22SetIdentity(Matrix22* matrix){
    matrix->lh = 1.0f;
    matrix->rh = 0.0f;
    matrix->ll = 0.0f;
    matrix->rl = 1.0f;
}

Matrix22 Matrix22Load(Matrix22* src, Matrix22* dest){
    dest->lh = src->lh;
    dest->rh = src->rh;
    dest->ll = src->ll;
    dest->rl = src->rl;

    return *dest;
}

Matrix22 Matrix22Add (Matrix22* lop, Matrix22* rop){
    Matrix22 ret;

    ret.lh = lop->lh + rop->lh;
    ret.rh = lop->rh + rop->rh;
    ret.ll = lop->ll + rop->ll;
    ret.rl = lop->rl + rop->rl;

    return ret;
}

Matrix22 Matrix22Sub (Matrix22* lop, Matrix22* rop){
    Matrix22 ret;

    ret.lh = lop->lh - rop->lh;
    ret.rh = lop->rh - rop->rh;
    ret.ll = lop->ll - rop->ll;
    ret.rl = lop->rl - rop->rl;

    return ret;
}

Matrix22 Matrix22MultMatrix22(Matrix22* matrix, Matrix22* matrix2){
    Matrix22 ret;

    ret.lh = matrix->lh * matrix2->lh + matrix->rh * matrix2->ll;
    ret.ll = matrix->ll * matrix2->lh + matrix->rl * matrix2->ll;
    ret.rh = matrix->lh * matrix2->rh + matrix->rh * matrix2->rl;
    ret.rl = matrix->ll * matrix2->rh + matrix->rl * matrix2->rl;

    return ret;
}

Vector2 Matrix22Transform(Matrix22* matrix, Vector2* op){
    Vector2 ret;

    ret.x = matrix->lh * op->x + matrix->rh * op->y;
    ret.y = matrix->ll * op->x + matrix->rl * op->y;

    return ret;
}

Matrix22 Matrix22Transpose(Matrix22* matrix){
    Matrix22 ret;

    float ll = matrix->ll;
    float rh = matrix->rh;

    ret.ll = rh;
    ret.rh = ll;

    return ret;
}

int Matrix22Invert(Matrix22* matrix, Matrix22* dest){
    // 1/det + adjicate
    float det = Matrix22Deter(matrix);

    if(det != 0){
        float invDet = 1.0f/det;

        dest->lh = matrix->rl * invDet;
        dest->ll = -(matrix->ll * invDet);
        dest->rl = matrix->lh * invDet;
        dest->rh = -(matrix->rh * invDet);

        return 1;
    }
    else{
        return 0;
    }
}

float Matrix22Deter(Matrix22* matrix){
    return matrix->lh * matrix->rl - matrix->ll * matrix->rh;
}

void negate(Matrix22* matrix){
    matrix->lh = -matrix->lh;
    matrix->rh = -matrix->rh;
    matrix->ll = -matrix->ll;
    matrix->rl = -matrix->rl;
}



