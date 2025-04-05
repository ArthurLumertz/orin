#include "orinmath.h"
#include <math.h>

/* ======================= */
/*      Utils Impl      */
/* ======================= */

Vector4f ColorToVector4f(Color color) {
    return (Vector4f) { color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f };
}


/* ======================= */
/*      Matrix4f Impl      */
/* ======================= */

Matrix4f IdentityMatrix4f() {
    Matrix4f matrix = {0};
    matrix.m00 = 1.0f;
    matrix.m11 = 1.0f;
    matrix.m22 = 1.0f;
    matrix.m33 = 1.0f;
    return matrix;
}

Matrix4f TranslateMatrix4f(Matrix4f matrix, Vector3f translation) {
    Matrix4f translationMatrix = IdentityMatrix4f();
    translationMatrix.m03 = translation.x;
    translationMatrix.m13 = translation.y;
    translationMatrix.m23 = translation.z;
    return MultiplyMatrix4f(translationMatrix, matrix);
}

Matrix4f ScaleMatrix4f(Matrix4f matrix, Vector3f scale) {
    Matrix4f scaleMatrix = IdentityMatrix4f();
    scaleMatrix.m00 = scale.x;
    scaleMatrix.m11 = scale.y;
    scaleMatrix.m22 = scale.z;
    return MultiplyMatrix4f(matrix, scaleMatrix);
}

Matrix4f RotateMatrix4f(Matrix4f matrix, Vector3f rotation) {
    float cosX = cosf(rotation.x);
    float sinX = sinf(rotation.x);
    float cosY = cosf(rotation.y);
    float sinY = sinf(rotation.y);
    float cosZ = cosf(rotation.z);
    float sinZ = sinf(rotation.z);

    Matrix4f rotationMatrix = IdentityMatrix4f();

    rotationMatrix.m00 = cosY * cosZ;
    rotationMatrix.m01 = -cosY * sinZ;
    rotationMatrix.m02 = sinY;

    rotationMatrix.m10 = cosX * sinZ + sinX * sinY * cosZ;
    rotationMatrix.m11 = cosX * cosZ - sinX * sinY * sinZ;
    rotationMatrix.m12 = -sinX * cosY;

    rotationMatrix.m20 = sinX * sinZ - cosX * sinY * cosZ;
    rotationMatrix.m21 = sinX * cosZ + cosX * sinY * sinZ;
    rotationMatrix.m22 = cosX * cosY;

    return MultiplyMatrix4f(matrix, rotationMatrix);
}

Matrix4f MultiplyMatrix4f(Matrix4f m1, Matrix4f m2) {
    Matrix4f result;

    result.m00 = m1.m00 * m2.m00 + m1.m01 * m2.m10 + m1.m02 * m2.m20 + m1.m03 * m2.m30;
    result.m01 = m1.m00 * m2.m01 + m1.m01 * m2.m11 + m1.m02 * m2.m21 + m1.m03 * m2.m31;
    result.m02 = m1.m00 * m2.m02 + m1.m01 * m2.m12 + m1.m02 * m2.m22 + m1.m03 * m2.m32;
    result.m03 = m1.m00 * m2.m03 + m1.m01 * m2.m13 + m1.m02 * m2.m23 + m1.m03 * m2.m33;

    result.m10 = m1.m10 * m2.m00 + m1.m11 * m2.m10 + m1.m12 * m2.m20 + m1.m13 * m2.m30;
    result.m11 = m1.m10 * m2.m01 + m1.m11 * m2.m11 + m1.m12 * m2.m21 + m1.m13 * m2.m31;
    result.m12 = m1.m10 * m2.m02 + m1.m11 * m2.m12 + m1.m12 * m2.m22 + m1.m13 * m2.m32;
    result.m13 = m1.m10 * m2.m03 + m1.m11 * m2.m13 + m1.m12 * m2.m23 + m1.m13 * m2.m33;

    result.m20 = m1.m20 * m2.m00 + m1.m21 * m2.m10 + m1.m22 * m2.m20 + m1.m23 * m2.m30;
    result.m21 = m1.m20 * m2.m01 + m1.m21 * m2.m11 + m1.m22 * m2.m21 + m1.m23 * m2.m31;
    result.m22 = m1.m20 * m2.m02 + m1.m21 * m2.m12 + m1.m22 * m2.m22 + m1.m23 * m2.m32;
    result.m23 = m1.m20 * m2.m03 + m1.m21 * m2.m13 + m1.m22 * m2.m23 + m1.m23 * m2.m33;

    result.m30 = m1.m30 * m2.m00 + m1.m31 * m2.m10 + m1.m32 * m2.m20 + m1.m33 * m2.m30;
    result.m31 = m1.m30 * m2.m01 + m1.m31 * m2.m11 + m1.m32 * m2.m21 + m1.m33 * m2.m31;
    result.m32 = m1.m30 * m2.m02 + m1.m31 * m2.m12 + m1.m32 * m2.m22 + m1.m33 * m2.m32;
    result.m33 = m1.m30 * m2.m03 + m1.m31 * m2.m13 + m1.m32 * m2.m23 + m1.m33 * m2.m33;

    return result;
}

Matrix4f OrthoMatrix4f(float left, float right, float bottom, float top, float near, float far) {
    Matrix4f matrix = IdentityMatrix4f();

    matrix.m00 = 2.0f / (right - left);
    matrix.m11 = 2.0f / (top - bottom);
    matrix.m22 = -2.0f / (far - near);
    matrix.m03 = -(right + left) / (right - left);
    matrix.m13 = -(top + bottom) / (top - bottom);
    matrix.m23 = -(far + near) / (far - near);
    matrix.m33 = 1.0f;

    return matrix;
}

Matrix4f InverseMatrix4f(Matrix4f m) {
    Matrix4f result = {0};

    float det = m.m00 * (m.m11 * (m.m22 * m.m33 - m.m23 * m.m32) - m.m12 * (m.m21 * m.m33 - m.m23 * m.m31) + m.m13 * (m.m21 * m.m32 - m.m22 * m.m31))
                - m.m01 * (m.m10 * (m.m22 * m.m33 - m.m23 * m.m32) - m.m12 * (m.m20 * m.m33 - m.m23 * m.m30) + m.m13 * (m.m20 * m.m32 - m.m22 * m.m30))
                + m.m02 * (m.m10 * (m.m21 * m.m33 - m.m23 * m.m31) - m.m11 * (m.m20 * m.m33 - m.m23 * m.m30) + m.m13 * (m.m20 * m.m31 - m.m21 * m.m30))
                - m.m03 * (m.m10 * (m.m21 * m.m32 - m.m22 * m.m31) - m.m11 * (m.m20 * m.m32 - m.m22 * m.m30) + m.m12 * (m.m20 * m.m31 - m.m21 * m.m30));

    if (det == 0) {
        return result;
    }

    float invDet = 1.0f / det;

    result.m00 = (m.m11 * (m.m22 * m.m33 - m.m23 * m.m32) - m.m12 * (m.m21 * m.m33 - m.m23 * m.m31) + m.m13 * (m.m21 * m.m32 - m.m22 * m.m31)) * invDet;
    result.m01 = -(m.m01 * (m.m22 * m.m33 - m.m23 * m.m32) - m.m02 * (m.m21 * m.m33 - m.m23 * m.m31) + m.m03 * (m.m21 * m.m32 - m.m22 * m.m31)) * invDet;
    result.m02 = (m.m01 * (m.m12 * m.m33 - m.m13 * m.m32) - m.m02 * (m.m11 * m.m33 - m.m13 * m.m31) + m.m03 * (m.m11 * m.m32 - m.m12 * m.m31)) * invDet;
    result.m03 = -(m.m01 * (m.m12 * m.m23 - m.m13 * m.m22) - m.m02 * (m.m11 * m.m23 - m.m13 * m.m21) + m.m03 * (m.m11 * m.m22 - m.m12 * m.m21)) * invDet;

    result.m10 = -(m.m10 * (m.m22 * m.m33 - m.m23 * m.m32) - m.m12 * (m.m20 * m.m33 - m.m23 * m.m30) + m.m13 * (m.m20 * m.m32 - m.m22 * m.m30)) * invDet;
    result.m11 = (m.m00 * (m.m22 * m.m33 - m.m23 * m.m32) - m.m02 * (m.m20 * m.m33 - m.m23 * m.m30) + m.m03 * (m.m20 * m.m32 - m.m22 * m.m30)) * invDet;
    result.m12 = -(m.m00 * (m.m12 * m.m33 - m.m13 * m.m32) - m.m02 * (m.m10 * m.m33 - m.m13 * m.m30) + m.m03 * (m.m10 * m.m32 - m.m12 * m.m30)) * invDet;
    result.m13 = (m.m00 * (m.m12 * m.m23 - m.m13 * m.m22) - m.m02 * (m.m10 * m.m23 - m.m13 * m.m20) + m.m03 * (m.m10 * m.m22 - m.m12 * m.m20)) * invDet;

    result.m20 = (m.m10 * (m.m21 * m.m33 - m.m23 * m.m31) - m.m11 * (m.m20 * m.m33 - m.m23 * m.m30) + m.m13 * (m.m20 * m.m31 - m.m21 * m.m30)) * invDet;
    result.m21 = -(m.m00 * (m.m21 * m.m33 - m.m23 * m.m31) - m.m01 * (m.m20 * m.m33 - m.m23 * m.m30) + m.m03 * (m.m20 * m.m31 - m.m21 * m.m30)) * invDet;
    result.m22 = (m.m00 * (m.m11 * m.m33 - m.m13 * m.m31) - m.m01 * (m.m10 * m.m33 - m.m13 * m.m30) + m.m03 * (m.m10 * m.m31 - m.m11 * m.m30)) * invDet;
    result.m23 = -(m.m00 * (m.m11 * m.m23 - m.m13 * m.m21) - m.m01 * (m.m10 * m.m23 - m.m13 * m.m20) + m.m03 * (m.m10 * m.m21 - m.m11 * m.m20)) * invDet;

    result.m30 = -(m.m10 * (m.m21 * m.m32 - m.m22 * m.m31) - m.m11 * (m.m20 * m.m32 - m.m22 * m.m30) + m.m12 * (m.m20 * m.m31 - m.m21 * m.m30)) * invDet;
    result.m31 = (m.m00 * (m.m21 * m.m32 - m.m22 * m.m31) - m.m01 * (m.m20 * m.m32 - m.m22 * m.m30) + m.m02 * (m.m20 * m.m31 - m.m21 * m.m30)) * invDet;
    result.m32 = -(m.m00 * (m.m11 * m.m32 - m.m12 * m.m31) - m.m01 * (m.m10 * m.m32 - m.m12 * m.m30) + m.m02 * (m.m10 * m.m31 - m.m11 * m.m30)) * invDet;
    result.m33 = (m.m00 * (m.m11 * m.m22 - m.m12 * m.m21) - m.m01 * (m.m10 * m.m22 - m.m12 * m.m20) + m.m02 * (m.m10 * m.m21 - m.m11 * m.m20)) * invDet;

    return result;
}

Matrix4f TransposeMatrix4f(Matrix4f m) {
    Matrix4f result = {0};

    result.m00 = m.m00;
    result.m01 = m.m10;
    result.m02 = m.m20;
    result.m03 = m.m30;
    result.m10 = m.m01;
    result.m11 = m.m11;
    result.m12 = m.m21;
    result.m13 = m.m31;
    result.m20 = m.m02;
    result.m21 = m.m12;
    result.m22 = m.m22;
    result.m23 = m.m32;
    result.m30 = m.m03;
    result.m31 = m.m13;
    result.m32 = m.m23;
    result.m33 = m.m33;

    return result;
}

Matrix4f InverseTransposeMatrix4f(Matrix4f m) {
    Matrix4f inverse = InverseMatrix4f(m);
    return TransposeMatrix4f(inverse);
}

float DegreesToRadians(float degrees) {
    return degrees * (M_PI / 180.0f);
}

float RadiansToDegrees(float radians) {
    return radians * (180.0f / M_PI);
}

/* ======================= */
/*      Vector2f Impl      */
/* ======================= */

Vector2f AddVector2f(Vector2f v1, Vector2f v2) {
    return (Vector2f){v1.x + v2.x, v1.y + v2.y};
}

Vector2f SubtractVector2f(Vector2f v1, Vector2f v2) {
    return (Vector2f){v1.x - v2.x, v1.y - v2.y};
}

Vector2f MultiplyVector2f(Vector2f v1, Vector2f v2) {
    return (Vector2f){v1.x * v2.x, v1.y * v2.y};
}

Vector2f DivideVector2f(Vector2f v1, Vector2f v2) {
    return (Vector2f){v1.x / v2.x, v1.y / v2.y};
}

float Vector2fLength(Vector2f v) {
    return sqrtf(v.x * v.x + v.y * v.y);
}

float Vector2fLengthSquared(Vector2f v) {
    return v.x * v.x + v.y * v.y;
}

float Vector2fDotProduct(Vector2f v1, Vector2f v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

float Vector2fCrossProduct(Vector2f v1, Vector2f v2) {
    return v1.x * v2.y - v1.y * v2.x;
}

Vector2f NormalizeVector2f(Vector2f v) {
    float length = Vector2fLength(v);
    if (length > 0) {
        return (Vector2f){v.x / length, v.y / length};
    }
    return v;
}

/* ======================= */
/*      Vector2i Impl      */
/* ======================= */

Vector2i AddVector2i(Vector2i v1, Vector2i v2) {
    return (Vector2i){v1.x + v2.x, v1.y + v2.y};
}

Vector2i SubtractVector2i(Vector2i v1, Vector2i v2) {
    return (Vector2i){v1.x - v2.x, v1.y - v2.y};
}

Vector2i MultiplyVector2i(Vector2i v1, Vector2i v2) {
    return (Vector2i){v1.x * v2.x, v1.y * v2.y};
}

Vector2i DivideVector2i(Vector2i v1, Vector2i v2) {
    return (Vector2i){v1.x / v2.x, v1.y / v2.y};
}

float Vector2iLength(Vector2i v) {
    return sqrtf((float)(v.x * v.x + v.y * v.y));
}

float Vector2iLengthSquared(Vector2i v) {
    return (float)(v.x * v.x + v.y * v.y);
}

float Vector2iDotProduct(Vector2i v1, Vector2i v2) {
    return (float)(v1.x * v2.x + v1.y * v2.y);
}

float Vector2iCrossProduct(Vector2i v1, Vector2i v2) {
    return (float)(v1.x * v2.y - v1.y * v2.x);
}

Vector2i NormalizeVector2i(Vector2i v) {
    float length = Vector2iLength(v);
    if (length > 0) {
        return (Vector2i){(int)(v.x / length), (int)(v.y / length)};
    }
    return v;
}

/* ======================= */
/*      Vector3f Impl      */
/* ======================= */

Vector3f AddVector3f(Vector3f v1, Vector3f v2) {
    return (Vector3f){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

Vector3f SubtractVector3f(Vector3f v1, Vector3f v2) {
    return (Vector3f){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

Vector3f MultiplyVector3f(Vector3f v1, Vector3f v2) {
    return (Vector3f){v1.x * v2.x, v1.y * v2.y, v1.z * v2.z};
}

Vector3f DivideVector3f(Vector3f v1, Vector3f v2) {
    return (Vector3f){v1.x / v2.x, v1.y / v2.y, v1.z / v2.z};
}

float Vector3fLength(Vector3f v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

float Vector3fLengthSquared(Vector3f v) {
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

float Vector3fDotProduct(Vector3f v1, Vector3f v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3f Vector3fCrossProduct(Vector3f v1, Vector3f v2) {
    return (Vector3f){
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    };
}

Vector3f NormalizeVector3f(Vector3f v) {
    float length = Vector3fLength(v);
    if (length > 0) {
        return (Vector3f){v.x / length, v.y / length, v.z / length};
    }
    return v;
}

/* ======================= */
/*      Vector3i Impl      */
/* ======================= */

Vector3i AddVector3i(Vector3i v1, Vector3i v2) {
    return (Vector3i){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

Vector3i SubtractVector3i(Vector3i v1, Vector3i v2) {
    return (Vector3i){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

Vector3i MultiplyVector3i(Vector3i v1, Vector3i v2) {
    return (Vector3i){v1.x * v2.x, v1.y * v2.y, v1.z * v2.z};
}

Vector3i DivideVector3i(Vector3i v1, Vector3i v2) {
    return (Vector3i){v1.x / v2.x, v1.y / v2.y, v1.z / v2.z};
}

float Vector3iLength(Vector3i v) {
    return sqrtf((float)(v.x * v.x + v.y * v.y + v.z * v.z));
}

float Vector3iLengthSquared(Vector3i v) {
    return (float)(v.x * v.x + v.y * v.y + v.z * v.z);
}

float Vector3iDotProduct(Vector3i v1, Vector3i v2) {
    return (float)(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

Vector3i Vector3iCrossProduct(Vector3i v1, Vector3i v2) {
    return (Vector3i){
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    };
}

Vector3i NormalizeVector3i(Vector3i v) {
    float length = Vector3iLength(v);
    if (length > 0) {
        return (Vector3i){
            (int)(v.x / length),
            (int)(v.y / length),
            (int)(v.z / length)
        };
    }
    return v;
}

/* ======================= */
/*      Vector4f Impl      */
/* ======================= */

Vector4f AddVector4f(Vector4f v1, Vector4f v2) {
    return (Vector4f){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w};
}

Vector4f SubtractVector4f(Vector4f v1, Vector4f v2) {
    return (Vector4f){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w};
}

Vector4f MultiplyVector4f(Vector4f v1, Vector4f v2) {
    return (Vector4f){v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w};
}

Vector4f DivideVector4f(Vector4f v1, Vector4f v2) {
    return (Vector4f){v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w};
}

float Vector4fLength(Vector4f v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

float Vector4fLengthSquared(Vector4f v) {
    return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
}

float Vector4fDotProduct(Vector4f v1, Vector4f v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

Vector4f NormalizeVector4f(Vector4f v) {
    float length = Vector4fLength(v);
    if (length > 0) {
        return (Vector4f){v.x / length, v.y / length, v.z / length, v.w / length};
    }
    return v;
}

/* ======================= */
/*      Vector4i Impl      */
/* ======================= */

Vector4i AddVector4i(Vector4i v1, Vector4i v2) {
    return (Vector4i){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w};
}

Vector4i SubtractVector4i(Vector4i v1, Vector4i v2) {
    return (Vector4i){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w};
}

Vector4i MultiplyVector4i(Vector4i v1, Vector4i v2) {
    return (Vector4i){v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w};
}

Vector4i DivideVector4i(Vector4i v1, Vector4i v2) {
    return (Vector4i){v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w};
}

float Vector4iLength(Vector4i v) {
    return sqrtf((float)(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w));
}

float Vector4iLengthSquared(Vector4i v) {
    return (float)(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

float Vector4iDotProduct(Vector4i v1, Vector4i v2) {
    return (float)(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
}

Vector4i NormalizeVector4i(Vector4i v) {
    float length = Vector4iLength(v);
    if (length > 0) {
        return (Vector4i){
            (int)(v.x / length),
            (int)(v.y / length),
            (int)(v.z / length),
            (int)(v.w / length)
        };
    }
    return v;
}

Vector2f LerpVector2f(Vector2f a, Vector2f b, float t) {
    return (Vector2f){
        a.x + (b.x - a.x) * t,
        a.y + (b.y - a.y) * t
    };
}

Vector2i LerpVector2i(Vector2i a, Vector2i b, float t) {
    return (Vector2i){
        (int)(a.x + (float)(b.x - a.x) * t + 0.5f),
        (int)(a.y + (float)(b.y - a.y) * t + 0.5f)
    };
}

Vector3f LerpVector3f(Vector3f a, Vector3f b, float t) {
    return (Vector3f){
        a.x + (b.x - a.x) * t,
        a.y + (b.y - a.y) * t,
        a.z + (b.z - a.z) * t
    };
}

Vector3i LerpVector3i(Vector3i a, Vector3i b, float t) {
    return (Vector3i){
        (int)(a.x + (float)(b.x - a.x) * t + 0.5f),
        (int)(a.y + (float)(b.y - a.y) * t + 0.5f),
        (int)(a.z + (float)(b.z - a.z) * t + 0.5f)
    };
}

Vector4f LerpVector4f(Vector4f a, Vector4f b, float t) {
    return (Vector4f){
        a.x + (b.x - a.x) * t,
        a.y + (b.y - a.y) * t,
        a.z + (b.z - a.z) * t,
        a.w + (b.w - a.w) * t
    };
}

Vector4i LerpVector4i(Vector4i a, Vector4i b, float t) {
    return (Vector4i){
        (int)(a.x + (float)(b.x - a.x) * t + 0.5f),
        (int)(a.y + (float)(b.y - a.y) * t + 0.5f),
        (int)(a.z + (float)(b.z - a.z) * t + 0.5f),
        (int)(a.w + (float)(b.w - a.w) * t + 0.5f)
    };
}

Vector2f NegateVector2f(Vector2f v) {
    return (Vector2f) { -v.x, -v.y };
}

Vector2i NegateVector2i(Vector2i v) {
    return (Vector2i) { -v.x, -v.y };
}

Vector3f NegateVector3f(Vector3f v) {
    return (Vector3f) { -v.x, -v.y, -v.z };
}

Vector3i NegateVector3i(Vector3i v) {
    return (Vector3i) { -v.x, -v.y, -v.z };
}

Vector4f NegateVector4f(Vector4f v) {
    return (Vector4f) { -v.x, -v.y, -v.z, -v.w };
}

Vector4i NegateVector4i(Vector4i v) {
    return (Vector4i) { -v.x, -v.y, -v.z, -v.w };
}