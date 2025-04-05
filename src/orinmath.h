#ifndef ORINMATH_H
#define ORINMATH_H

#include "orin.h"

#ifdef __cplusplus
extern "C" {
#endif


Matrix4f IdentityMatrix4f();
Matrix4f TranslateMatrix4f(Matrix4f matrix, Vector3f translation);
Matrix4f ScaleMatrix4f(Matrix4f matrix, Vector3f scale);
Matrix4f RotateMatrix4f(Matrix4f matrix, Vector3f rotation);
Matrix4f MultiplyMatrix4f(Matrix4f m1, Matrix4f m2);

Matrix4f InverseMatrix4f(Matrix4f m);
Matrix4f TransposeMatrix4f(Matrix4f m);
Matrix4f InverseTransposeMatrix4f(Matrix4f m);

Matrix4f OrthoMatrix4f(float left, float right, float bottom, float top, float near, float far);

float DegreesToRadians(float degrees);
float RadiansToDegrees(float radians);

Vector2f AddVector2f(Vector2f v1, Vector2f v2);
Vector2f SubtractVector2f(Vector2f v1, Vector2f v2);
Vector2f MultiplyVector2f(Vector2f v1, Vector2f v2);
Vector2f DivideVector2f(Vector2f v1, Vector2f v2);
float Vector2fLength(Vector2f v);
float Vector2fLengthSquared(Vector2f v);
float Vector2fDotProduct(Vector2f v1, Vector2f v2);
float Vector2fCrossProduct(Vector2f v1, Vector2f v2);
Vector2f NormalizeVector2f(Vector2f v);
Vector2f LerpVector2f(Vector2f a, Vector2f b, float t);

Vector2i AddVector2i(Vector2i v1, Vector2i v2);
Vector2i SubtractVector2i(Vector2i v1, Vector2i v2);
Vector2i MultiplyVector2i(Vector2i v1, Vector2i v2);
Vector2i DivideVector2i(Vector2i v1, Vector2i v2);
float Vector2iLength(Vector2i v);
float Vector2iLengthSquared(Vector2i v);
float Vector2iDotProduct(Vector2i v1, Vector2i v2);
float Vector2iCrossProduct(Vector2i v1, Vector2i v2);
Vector2i NormalizeVector2i(Vector2i v);
Vector2i LerpVector2i(Vector2i a, Vector2i b, float t);

Vector3f AddVector3f(Vector3f v1, Vector3f v2);
Vector3f SubtractVector3f(Vector3f v1, Vector3f v2);
Vector3f MultiplyVector3f(Vector3f v1, Vector3f v2);
Vector3f DivideVector3f(Vector3f v1, Vector3f v2);
float Vector3fLength(Vector3f v);
float Vector3fLengthSquared(Vector3f v);
float Vector3fDotProduct(Vector3f v1, Vector3f v2);
Vector3f Vector3fCrossProduct(Vector3f v1, Vector3f v2);
Vector3f NormalizeVector3f(Vector3f v);
Vector3f LerpVector3f(Vector3f a, Vector3f b, float t);

Vector3i AddVector3i(Vector3i v1, Vector3i v2);
Vector3i SubtractVector3i(Vector3i v1, Vector3i v2);
Vector3i MultiplyVector3i(Vector3i v1, Vector3i v2);
Vector3i DivideVector3i(Vector3i v1, Vector3i v2);
float Vector3iLength(Vector3i v);
float Vector3iLengthSquared(Vector3i v);
float Vector3iDotProduct(Vector3i v1, Vector3i v2);
Vector3i Vector3iCrossProduct(Vector3i v1, Vector3i v2);
Vector3i NormalizeVector3i(Vector3i v);
Vector3i LerpVector3i(Vector3i a, Vector3i b, float t);

Vector4f AddVector4f(Vector4f v1, Vector4f v2);
Vector4f SubtractVector4f(Vector4f v1, Vector4f v2);
Vector4f MultiplyVector4f(Vector4f v1, Vector4f v2);
Vector4f DivideVector4f(Vector4f v1, Vector4f v2);
float Vector4fLength(Vector4f v);
float Vector4fLengthSquared(Vector4f v);
float Vector4fDotProduct(Vector4f v1, Vector4f v2);
Vector4f NormalizeVector4f(Vector4f v);
Vector4f LerpVector4f(Vector4f v1, Vector4f v2, float t);

Vector4i AddVector4i(Vector4i v1, Vector4i v2);
Vector4i SubtractVector4i(Vector4i v1, Vector4i v2);
Vector4i MultiplyVector4i(Vector4i v1, Vector4i v2);
Vector4i DivideVector4i(Vector4i v1, Vector4i v2);
float Vector4iLength(Vector4i v);
float Vector4iLengthSquared(Vector4i v);
float Vector4iDotProduct(Vector4i v1, Vector4i v2);
Vector4i NormalizeVector4i(Vector4i v);
Vector4i LerpVector4i(Vector4i a, Vector4i b, float t);

Vector2f NegateVector2f(Vector2f v);
Vector2i NegateVector2i(Vector2i v);
Vector3f NegateVector3f(Vector3f v);
Vector3i NegateVector3i(Vector3i v);
Vector4f NegateVector4f(Vector4f v);
Vector4i NegateVector4i(Vector4i v);

#ifdef __cplusplus
}
#endif

#endif
