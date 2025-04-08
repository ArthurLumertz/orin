#ifndef ORINMATH_H
#define ORINMATH_H

#include "orin.h"

#define PI      3.14159265358979323846f
#define PI2     (PI * 2)

#ifdef __cplusplus
extern "C" {
#endif

ORAPI inline double MaxD(double a, double b);
ORAPI inline float MaxF(float a, float b);
ORAPI inline int MaxI(int a, int b);
ORAPI inline double MinD(double a, double b);
ORAPI inline float MinF(float a, float b);
ORAPI inline int MinI(int a, int b);

ORAPI inline double ClampD(double value, double min, double max);
ORAPI inline float ClampF(float value, float min, float max);
ORAPI inline int ClampI(int value, int min, int max);

ORAPI inline double LerpD(double a, double b, double t);
ORAPI inline float LerpF(float a, float b, float t);

ORAPI inline float Normalize(float value, float min, float max);
ORAPI inline float DegreesToRadians(float degrees);
ORAPI inline float RadiansToDegrees(float radians);

ORAPI void IdentityMatrix4f(Matrix4f *result);
ORAPI void TranslateMatrix4f(Matrix4f *result, const Matrix4f *matrix, Vector3f translation);
ORAPI void ScaleMatrix4f(Matrix4f *result, const Matrix4f *matrix, Vector3f scale);
ORAPI void RotateMatrix4f(Matrix4f *result, const Matrix4f *matrix, Vector3f rotation);
ORAPI void MultiplyMatrix4f(Matrix4f *result, const Matrix4f *m1, const Matrix4f *m2);
ORAPI void InverseMatrix4f(Matrix4f *result, const Matrix4f *m);
ORAPI void TransposeMatrix4f(Matrix4f *result, const Matrix4f *m);
ORAPI void InverseTransposeMatrix4f(Matrix4f *result, const Matrix4f *m);
ORAPI void OrthoMatrix4f(Matrix4f *result, float left, float right, float bottom, float top, float near, float far);

ORAPI Vector2f AddVector2f(Vector2f v1, Vector2f v2);
ORAPI Vector2f SubtractVector2f(Vector2f v1, Vector2f v2);
ORAPI Vector2f MultiplyVector2f(Vector2f v1, Vector2f v2);
ORAPI Vector2f DivideVector2f(Vector2f v1, Vector2f v2);
ORAPI float Vector2fLength(Vector2f v);
ORAPI float Vector2fLengthSquared(Vector2f v);
ORAPI float Vector2fDotProduct(Vector2f v1, Vector2f v2);
ORAPI float Vector2fCrossProduct(Vector2f v1, Vector2f v2);
ORAPI Vector2f NormalizeVector2f(Vector2f v);
ORAPI Vector2f LerpVector2f(Vector2f a, Vector2f b, float t);

ORAPI Vector2i AddVector2i(Vector2i v1, Vector2i v2);
ORAPI Vector2i SubtractVector2i(Vector2i v1, Vector2i v2);
ORAPI Vector2i MultiplyVector2i(Vector2i v1, Vector2i v2);
ORAPI Vector2i DivideVector2i(Vector2i v1, Vector2i v2);
ORAPI float Vector2iLength(Vector2i v);
ORAPI float Vector2iLengthSquared(Vector2i v);
ORAPI float Vector2iDotProduct(Vector2i v1, Vector2i v2);
ORAPI float Vector2iCrossProduct(Vector2i v1, Vector2i v2);
ORAPI Vector2i NormalizeVector2i(Vector2i v);
ORAPI Vector2i LerpVector2i(Vector2i a, Vector2i b, float t);

ORAPI Vector3f AddVector3f(Vector3f v1, Vector3f v2);
ORAPI Vector3f SubtractVector3f(Vector3f v1, Vector3f v2);
ORAPI Vector3f MultiplyVector3f(Vector3f v1, Vector3f v2);
ORAPI Vector3f DivideVector3f(Vector3f v1, Vector3f v2);
ORAPI float Vector3fLength(Vector3f v);
ORAPI float Vector3fLengthSquared(Vector3f v);
ORAPI float Vector3fDotProduct(Vector3f v1, Vector3f v2);
ORAPI Vector3f Vector3fCrossProduct(Vector3f v1, Vector3f v2);
ORAPI Vector3f NormalizeVector3f(Vector3f v);
ORAPI Vector3f LerpVector3f(Vector3f a, Vector3f b, float t);

ORAPI Vector3i AddVector3i(Vector3i v1, Vector3i v2);
ORAPI Vector3i SubtractVector3i(Vector3i v1, Vector3i v2);
ORAPI Vector3i MultiplyVector3i(Vector3i v1, Vector3i v2);
ORAPI Vector3i DivideVector3i(Vector3i v1, Vector3i v2);
ORAPI float Vector3iLength(Vector3i v);
ORAPI float Vector3iLengthSquared(Vector3i v);
ORAPI float Vector3iDotProduct(Vector3i v1, Vector3i v2);
ORAPI Vector3i Vector3iCrossProduct(Vector3i v1, Vector3i v2);
ORAPI Vector3i NormalizeVector3i(Vector3i v);
ORAPI Vector3i LerpVector3i(Vector3i a, Vector3i b, float t);

ORAPI Vector4f AddVector4f(Vector4f v1, Vector4f v2);
ORAPI Vector4f SubtractVector4f(Vector4f v1, Vector4f v2);
ORAPI Vector4f MultiplyVector4f(Vector4f v1, Vector4f v2);
ORAPI Vector4f DivideVector4f(Vector4f v1, Vector4f v2);
ORAPI float Vector4fLength(Vector4f v);
ORAPI float Vector4fLengthSquared(Vector4f v);
ORAPI float Vector4fDotProduct(Vector4f v1, Vector4f v2);
ORAPI Vector4f NormalizeVector4f(Vector4f v);
ORAPI Vector4f LerpVector4f(Vector4f v1, Vector4f v2, float t);

ORAPI Vector4i AddVector4i(Vector4i v1, Vector4i v2);
ORAPI Vector4i SubtractVector4i(Vector4i v1, Vector4i v2);
ORAPI Vector4i MultiplyVector4i(Vector4i v1, Vector4i v2);
ORAPI Vector4i DivideVector4i(Vector4i v1, Vector4i v2);
ORAPI float Vector4iLength(Vector4i v);
ORAPI float Vector4iLengthSquared(Vector4i v);
ORAPI float Vector4iDotProduct(Vector4i v1, Vector4i v2);
ORAPI Vector4i NormalizeVector4i(Vector4i v);
ORAPI Vector4i LerpVector4i(Vector4i a, Vector4i b, float t);

ORAPI Vector2f NegateVector2f(Vector2f v);
ORAPI Vector2i NegateVector2i(Vector2i v);
ORAPI Vector3f NegateVector3f(Vector3f v);
ORAPI Vector3i NegateVector3i(Vector3i v);
ORAPI Vector4f NegateVector4f(Vector4f v);
ORAPI Vector4i NegateVector4i(Vector4i v);

#ifdef __cplusplus
}
#endif

#endif
