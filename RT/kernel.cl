#pragma OPENCL EXTENSION cl_khr_fp64 : enable
#define EPS 		1.0e-3f
#define TRC 		0.333333333333333
#define T_W 		512
#define T_S 		262144

typedef struct
{
	float4		dir;
	float4		right;
	float4		up;
	float4		position;
	bool		initialized;
} Camera;

typedef enum
{
	SPHERE = 0,
	PLANE,
	CONE,
	CYLINDER,
	DISK,
	MOBIUS,
	TORUS,
	TRIANGLE,
	PARABOLA,
	ELLIPS,
	PRIMITIVE_TYPES_AMOUNT
} PrimitiveType;

typedef enum
{
	DEFAULT = 0,
	CHECKERBOARD,
	GRID,
	BRICK,
	PERLIN,
	NORMAL_DISRUP,
	TEXTURE_1,
	TEXTURE_2,
	TEXTURE_3

} ProceduralType;

typedef struct  	s_plane
{
	float4			position;
	float4			normal;
} Plane;

typedef struct
{
	float4		position;
	float		r2;
} Sphere;

typedef struct
{
	float4		position;
	float4		axis;
	float		r;
	float		h;
} Cylinder;

typedef struct
{
	float4		position;
	float4		axis;
	float		angle;
	float		h;
} Cone;

typedef struct
{
	float4		position;
	float4		normal;
	float		r;
} Disk;

typedef struct
{
	float4		position;
	float4		axis;
	float		r;
	float		a;
} Ellips;

typedef struct
{
	float4		position;
	float4		axis;
	float		a;
} Parabola;

typedef struct
{
	float4		position;
	float4		axis;
	float		r1;
	float		r2;
} Torus;

typedef struct
{
	float4		point_a;
	float4		point_b;
	float4		point_c;
} Triangle;

typedef struct
{
	float4		position;
	float4		axis_x;
	float4		axis_y;
	float		r;
	float		a;
} Mobius;

typedef union
{
	Plane		p;
	Disk		d;
	Sphere		s;
	Cylinder	cyl;
	Cone		cone;
	Ellips		el;
	Parabola	par;
	Torus		tor;
	Triangle	tri;
	Mobius		mob;
} Primitive;

typedef struct
{
	Primitive	primitive;
	float4		color;
	float4		color2;
	float		ambient;
	float		reflect;
	float		transparency;
	float		refract;
	int			specular;
	int			type;
	int			proced;
	float		scale;
	float		horiz_shift;
	float		vertic_shift;
} Object;

typedef struct
{
	Primitive	primitive;
	float		intensity;
	int			type;
} Light;

typedef struct
{
	uchar4					a[T_S];
	uchar4					b[T_S];
	uchar4					c[T_S];
}							Texture;

typedef struct
{
	float4 o;
	float4 d;
} Ray;

typedef struct
{
	Ray			ray;
	float4		radiance;
} PixelDesc;

typedef struct {
	float4	normal;
	float	t;
	int		intersected_obj;
} IntersectionDesc;

typedef struct		s_root
{
	double4			a;
	int				order;
}					t_root;

typedef struct	s_figure
{
	float4		point;
	float4		normal;
	float4		ray;
	float4		color;
	float4		color2;
	float		reflect;
	float		refract;
	float		transparency;
	int			type;
	int			id;
	int			proced;
	float		scale;
	float		horiz_shift;
	float		vertic_shift;
}				t_figure;

double			get_rootx(double8 poli, float lim);
double			get_root(t_root r, float2 lim);
double8			canon_poli(double8 poli);
t_root			solve_foe(double8 poli);
t_root			solve_soe(double8 poli);
t_root			solve_toe(double8 poli);
t_root			solve_boe(double8 poli);
t_root			solve_coe(double8 poli);
t_root			solve_qoe(double8 poli);
double			determinant(float4 a, float4 b, float4 c);

double			get_root(t_root r, float2 lim)
{
	double		t;

	if (r.order > 4)
		return (lim.x);
	else if (r.order > 3 && r.a.w >= lim.x && r.a.w < lim.y)
	{
		t = (r.a.z >= lim.x && r.a.z < lim.y && r.a.z < r.a.w) ? r.a.z : r.a.w;
		t = (r.a.y >= lim.x && r.a.y < lim.y && r.a.y < t) ? r.a.y : t;
		t = (r.a.x >= lim.x && r.a.x < lim.y && r.a.x < t) ? r.a.x : t;
	}
	else if (r.order > 2 && r.a.z >= lim.x && r.a.z < lim.y)
	{
		t = (r.a.y >= lim.x && r.a.y < lim.y && r.a.y < r.a.z) ? r.a.y : r.a.z;
		t = (r.a.x >= lim.x && r.a.x < lim.y && r.a.x < t) ? r.a.x : t;
	}
	else if (r.order > 1 && r.a.y >= lim.x && r.a.y < lim.y)
		t = (r.a.x >= lim.x && r.a.x < lim.y && r.a.x < r.a.y) ? r.a.x : r.a.y;
	else if (r.order > 0 && r.a.x >= lim.x && r.a.x < lim.y)
		t = r.a.x;
	else
		return (lim.y);
	return (t);
}

double8			canon_poli(double8 poli)
{
	double8		tmp;

	if (poli[0])
		tmp = (double8)(1.0, poli[1] / poli[0], poli[2] / poli[0], poli[3] / poli[0], poli[4] / poli[0], 0.0, 0.0, 0.0);
	else if (poli[1])
		tmp = (double8)(0.0, 1.0, poli[2] / poli[1], poli[3] / poli[1], poli[4] / poli[1], 0.0, 0.0, 0.0);
	else if (poli[2])
		tmp = (double8)(0.0, 0.0, 1.0, poli[3] / poli[2], poli[4] / poli[2], 0.0, 0.0, 0.0);
	else if (poli[3])
		tmp = (double8)(0.0, 0.0, 0.0, 1.0, poli[4] / poli[3], 0.0, 0.0, 0.0);
	else
		tmp = poli;
	return (tmp);
}

t_root			solve_foe(double8 poli)
{
	poli = canon_poli(poli);
	if (poli[3])
		return ((t_root){(double4)(-poli[4], 0.0, 0.0, 0.0), 1});
	else if (!poli[3] && !poli[4])
		return ((t_root){(double4)(0.0), 5});
	else
		return ((t_root){(double4)(0.0), 0});
}

t_root			solve_soe(double8 poli)
{
	double		p;
	double		q;
	double		r;

	if (!poli[2])
		return (solve_foe(poli));
	poli = canon_poli(poli);
	if (poli[3])
	{
		r = pown(poli[3], 2) - 4.0 * poli[4];
		if (r < 0.0f)
			return ((t_root){(double4)(0.0), 0});
		p = -poli[3] * 0.5;
		if (r == 0.0)
			return ((t_root){(double4)(p, p, 0.0, 0.0), 2});
		q = sqrt(r) * 0.5;
		return ((t_root){(double4)(p - q, p + q, 0.0, 0.0), 2});
	}
	if (poli[4] > 0.0)
		return ((t_root){(double4)(0.0), 0});
	q = sqrt(-poli[4]);
	return ((t_root){(double4)(q, -q, 0.0, 0.0), 2});
}

t_root			solve_toe(double8 poli)
{
	double8		pqr;
	t_root		tmp;
	double		p;

	if (!poli[1])
		return (solve_soe(poli));
	poli = canon_poli(poli);
	pqr[0] = poli[2] ? poli[3] - pown(poli[2], 2) * TRC : poli[3];
	pqr[1] = poli[2] ? poli[4] + 2.0 * pown(poli[2], 3) * pown(TRC, 3) - poli[2] * poli[3] * TRC : poli[4];
	pqr[2] = pown(pqr[1], 2) * 0.25 + pown(pqr[0], 3) * pown(TRC, 3);
	if (pqr[2] > 0.0)
	{
		p = sqrt(pqr[2]);
		p = cbrt(-pqr[1] * 0.5 + p) + cbrt(-pqr[1] * 0.5 - p) - poli[2] * TRC;
		return ((t_root){(double4)(p, 0.0, 0.0, 0.0), 1});
	}
	p = pown(pqr[1], 2) * 0.25 - pqr[2];
	p = 2 * rootn(p, 6) * cos(atan(2.0 * sqrt(-pqr[2]) / pqr[1]) * TRC);
	p = ((pqr[1] > 0.0) ? -p : p) - poli[2] * TRC;
	pqr = (double8)(0.0, 0.0, 1.0, p + poli[2], pown(p, 2) + poli[2] * p + poli[3], 0.0, 0.0, 0.0);
	tmp = solve_soe(pqr);
	return ((t_root){(double4)(p, tmp.a.x, tmp.a.y, 0.0), 3});
}

t_root			solve_boe(double8 poli)
{
	t_root		tmp;
	double		p;
	double		q;

	if (!poli[0])
		return (solve_toe(poli));
	poli = canon_poli(poli);
	tmp = solve_soe((double8)(0.0, 0.0, 1.0, poli[2], poli[4], 0.0, 0.0, 0.0));
	p = tmp.a.x >= 0.0 ? sqrt(tmp.a.x) : -1.0;
	q = tmp.a.y >= 0.0 ? sqrt(tmp.a.y) : -1.0;
	if (tmp.order == 2 && p != -1.0 && q != -1.0)
		return ((t_root){(double4)(p, -p, q, -q), 4});
	if (tmp.order == 2 && p != -1.0 && q == -1.0)
		return ((t_root){(double4)(p, -p, 0.0, 0.0), 2});
	if (tmp.order == 2 && p == -1.0 && q != -1.0)
		return ((t_root){(double4)(q, -q, 0.0, 0.0), 2});
	return ((t_root){(double4)(0.0), 0});
}

t_root			solve_coe(double8 poli)
{
	double8		pqr;
	t_root		tmp;
	t_root		x;
	t_root		y;
	double		p;

	if (!poli[0])
		return (solve_toe(poli));
	if (!poli[3])
		return (solve_boe(poli));
	poli = canon_poli(poli);
	pqr = (double8)(0.0, 1.0, 2.0 * poli[2], pown(poli[2], 2) - 4.0 * poli[4], -pown(poli[3], 2), 0.0, 0.0, 0.0);
	tmp = solve_toe(pqr);
	if (tmp.order > 0)
	{
		if (tmp.a.x >= 0)
			p = sqrt(tmp.a.x);
		else if (tmp.order > 1 && tmp.a.y >= 0.0)
			p = sqrt(x.a.y);
		else if (tmp.order > 2 && tmp.a.z >= 0.0)
			p = sqrt(tmp.a.z);
		else
			return ((t_root){(double4)(0.0f), 0});
		x = solve_soe((double8)(0.0, 0.0, 1.0, p, (poli[2] + pown(p, 2) - poli[3] / p) * 0.5, 0.0, 0.0, 0.0));
		y = solve_soe((double8)(0.0, 0.0, 1.0, -p, (poli[2] + pown(p, 2) + poli[3] / p) * 0.5, 0.0, 0.0, 0.0));
		if (x.order == 2 && y.order == 2)
			return ((t_root){(double4)(x.a.x, x.a.y, y.a.x, y.a.y), 4});
		else
			return ((x.order == 2) ? x : y);
	}
	return ((t_root){(double4)(0.0f), 0});
}

t_root			solve_qoe(double8 poli)
{
	double8		pqr;
	t_root		tmp;

	if (!poli[0])
		return (solve_toe(poli));
	if (!poli[1])
		return (solve_coe(poli));
	poli = canon_poli(poli);
	pqr = (double8)(1, 0,
		poli[2] - pown(poli[1], 2) * 0.375,
		pown(poli[1], 3) * 0.125 - poli[1] * poli[2] * 0.5 + poli[3],
		poli[2] * pown(poli[1], 2) * 0.0625 + poli[4] - pown(poli[1], 4) * 0.01171875 - poli[1] * poli[3] * 0.25,
		0.0, 0.0, 0.0);
	tmp = solve_coe(pqr);
	if (tmp.order != 0)
	{
		tmp.a.x -= poli[1] * 0.25;
		tmp.a.y -= poli[1] * 0.25;
	}
	if (tmp.order == 4)
	{
		tmp.a.z -= poli[1] * 0.25;
		tmp.a.w -= poli[1] * 0.25;
	}
	return (tmp);
}

double			determinant(float4 a, float4 b, float4 c)
{
	double		tmp;

	tmp = a.x * b.y * c.z - a.x * b.z * c.y
		+ a.y * b.z * c.x - a.y * b.x * c.z
		+ a.z * b.x * c.y - a.z * b.y * c.x;
	return (tmp);
}

double			intersect_plane(__global Plane *obj, Ray ray, float2 lim);
float4			normal_plane(__global Plane *obj, Ray ray);
double			intersect_disk(__global Disk *obj, Ray ray, float2 lim);
float4			normal_disk(__global Disk *obj, Ray ray);
double			intersect_sphere(__global Sphere *obj, Ray ray, float2 lim);
float4			normal_sphere(__global Sphere *obj, Ray ray, float t);
double			intersect_cone(__global Cone *obj, Ray ray, float2 lim);
float4			normal_cone(__global Cone *obj, Ray ray, float t);
double			intersect_cylinder(__global Cylinder *obj, Ray ray, float2 lim);
float4			normal_cylinder(__global Cylinder *obj, Ray ray, float t);
double			intersect_ellipsoid(__global Ellips *obj, Ray ray, float2 lim);
float4			normal_ellipsoid(__global Ellips *obj, Ray ray, float t);
double			intersect_parabola(__global Parabola *obj, Ray ray, float2 lim);
float4			normal_parabola(__global Parabola *obj, Ray ray, float t);
double			intersect_torus(__global Torus *obj, Ray ray, float2 lim);
float4			normal_torus(__global Torus *obj, Ray ray, float t);
double			intersect_triangle(__global Triangle *obj, Ray ray, float2 lim);
float4			normal_triangle(__global Triangle *obj, Ray ray);
float4			ch_base_vec(float4 a, float4 b, float4 c);
t_root			limit_mobius(__global Mobius *obj, Ray ray, t_root tmp);
double			intersect_mobius(__global Mobius *obj, Ray ray, float2 lim);
float4			normal_mobius(__global Mobius *obj, Ray ray, float t);

double			intersect_plane(__global Plane *obj, Ray ray, float2 lim)
{
	double8		poli;
	float4		x;
	t_root		tmp;
	double		t;

	if (!obj || !length(ray.d))
		return (INFINITY);
	x = ray.o - obj->position;
	poli = (double8)(0.0, 0.0, 0.0,
		dot(obj->normal, ray.d),
		dot(obj->normal, x),
		0.0, 0.0, 0.0);
	tmp = solve_foe(poli);
	t = get_root(tmp, lim);
	return (t);
}

float4			normal_plane(__global Plane *obj, Ray ray)
{
	float4		tmp;
	double		a;

	tmp = (float4)(0.0);
	if (obj)
	{
		tmp = obj->normal;
		a = dot(tmp, ray.d);
		if (a > 0.0)
			tmp = -tmp;
	}
	return (tmp);
}

double			intersect_disk(__global Disk *obj, Ray ray, float2 lim)
{
	double8		poli;
	float4		x;
	t_root		tmp;
	double		t;

	if (!obj || !length(ray.d))
		return (INFINITY);
	x = ray.o - obj->position;
	poli = (double8)(0.0, 0.0, 0.0,
		dot(obj->normal, ray.d),
		dot(obj->normal, x),
		0.0, 0.0, 0.0);
	tmp = solve_foe(poli);
	t = get_root(tmp, lim);
	if (t >= lim.x && t < lim.y)
	{
		x = ray.o + ray.d * convert_float(t);
		if (fast_distance(x, obj->position) <= obj->r)
			return (t);
	}
	return (INFINITY);
}

float4			normal_disk(__global Disk *obj, Ray ray)
{
	float4		tmp;
	double		a;

	tmp = (float4)(0.0);
	if (obj)
	{
		tmp = obj->normal;
		a = dot(tmp, ray.d);
		if (a > 0.0)
			tmp = -tmp;
	}
	return (tmp);
}

double			intersect_sphere(__global Sphere *obj, Ray ray, float2 lim)
{
	double8		poli;
	float4		x;
	t_root		tmp;
	double		t;

	if (!obj || !length(ray.d))
		return (INFINITY);
	x = ray.o - obj->position;
	poli = (double8)(0.0, 0.0, 1.0,
		2.0 * dot(ray.d, x),
		dot(x, x) - obj->r2,
		0.0, 0.0, 0.0);
	tmp = solve_soe(poli);
	t = get_root(tmp, lim);
	return (t);
}

float4			normal_sphere(__global Sphere *obj, Ray ray, float t)
{
	float4		tmp;

	tmp = (float4)(0.0);
	if (obj)
		tmp = normalize(ray.d * t + ray.o - obj->position);
	return (tmp);
}

double			intersect_cone(__global Cone *obj, Ray ray, float2 lim)
{
	double8		poli;
	float4		x;
	t_root		tmp;
	double		t;
	double		a;
	double		b;
	double		k;
	double		m;

	if (!obj || !length(ray.d))
		return (INFINITY);
	x = ray.o - obj->position;
	a = dot(obj->axis, x);
	b = dot(obj->axis, ray.d);
	k = 1.0 + pown(tan(obj->angle), 2);
	poli = (double8)(0.0, 0.0,
		1.0 - pown(b, 2) * k,
		2.0 * (dot(x, ray.d) - a * b * k),
		dot(x, x) - pown(a, 2) * k,
		0.0, 0.0, 0.0);
	tmp = solve_soe(poli);
	t = get_root(tmp, lim);
	m = b * t + a;
	if (m <= 0 && m > -obj->h)
		return (t);
	lim.x = t + EPS;
	t = get_root(tmp, lim);
	m = b * t + a;
	if (m <= 0 && m > -obj->h)
		return (t);
	return (INFINITY);
}

float4			normal_cone(__global Cone *obj, Ray ray, float t)
{
	float4		tmp;
	float4		x;
	float		k;

	tmp = (float4)(0.0);
	if (obj)
	{
		x = ray.d * t + ray.o - obj->position;
		k = 1.0 + pown(tan(obj->angle), 2);
		tmp = normalize(x - obj->axis * dot(obj->axis, x) * k);
	}
	return (tmp);
}

double			intersect_cylinder(__global Cylinder *obj, Ray ray, float2 lim)
{
	double8		poli;
	float4		x;
	t_root		tmp;
	double		t;
	double		a;
	double		b;
	double		m;
	double		half_h;

	if (!obj || !length(ray.d))
		return (INFINITY);
	x = ray.o - obj->position;
	a = dot(obj->axis, x);
	b = dot(obj->axis, ray.d);
	poli = (double8)(0.0, 0.0,
		1.0 - pown(b, 2),
		2.0 * (dot(x, ray.d) - b * a),
		dot(x, x) - pown(a, 2) - pown(obj->r, 2),
		0.0, 0.0, 0.0);
	tmp = solve_soe(poli);
	t = get_root(tmp, lim);
	m = b * t + a;
	if (obj->h < 0 || obj->h == INFINITY)
		return (INFINITY);
	half_h = obj->h * 0.5;
	if (m < half_h && m > -half_h)
		return (t);
	lim.x = t + EPS;
	t = get_root(tmp, lim);
	m = b * t + a;
	if (m < half_h && m > -half_h)
		return (t);
	return (INFINITY);
}

float4			normal_cylinder(__global Cylinder *obj, Ray ray, float t)
{
	float4		tmp;
	float4		x;

	tmp = (float4)(0.0);
	if (obj)
	{
		x = ray.d * t + ray.o - obj->position;
		tmp = normalize(x - obj->axis * dot(obj->axis, x));
	}
	return (tmp);
}

double			intersect_ellipsoid(__global Ellips *obj, Ray ray, float2 lim)
{
	double8		poli;
	float4		x;
	t_root		tmp;
	double		t;
	double		a;
	double		b;
	double		c;

	if (!obj || !length(ray.d))
		return (INFINITY);
	x = ray.o - obj->position;
	a = pown(obj->r, 2);
	b = 2.0 * obj->a * dot(obj->axis, ray.d);
	c = a + obj->a * (2.0 * dot(obj->axis, x) - 1.0);
	poli = (double8)(0.0, 0.0,
		4.0 * a - b * b,
		8.0 * a * dot(ray.d, x) - 2.0 * b * c,
		4.0 * a * dot(x, x) - c * c,
		0.0, 0.0, 0.0);
	tmp = solve_soe(poli);
	t = get_root(tmp, lim);
	return (t);
}

float4			normal_ellipsoid(__global Ellips *obj, Ray ray, float t)
{
	float4		tmp;
	float4		x;
	float4		y;
	float		a;

	tmp = (float4)(0.0);
	if (obj)
	{
		x = obj->position + obj->axis * obj->a * 0.5f;
		y = ray.d * t + ray.o - x;
		a = pown(obj->a / obj->r, 2) * dot(obj->axis, y);
		tmp = normalize(y - obj->axis * a);
	}
	return (tmp);
}

double			intersect_parabola(__global Parabola *obj, Ray ray, float2 lim)
{
	double8		poli;
	float4		x;
	t_root		tmp;
	double		t;
	double		a;
	double		b;

	if (!obj || !length(ray.d))
		return (INFINITY);
	x = ray.o - obj->position;
	a = dot(obj->axis, x);
	b = dot(obj->axis, ray.d);
	poli = (double8)(0.0, 0.0,
		1.0 - pown(b, 2),
		2.0 * dot(ray.d, x) - 2.0 * b * (a + 2.0 * obj->a),
		dot(x, x) - a * (a + 4.0 * obj->a),
		0.0, 0.0, 0.0);
	tmp = solve_soe(poli);
	t = get_root(tmp, lim);
	return (t);
}

float4			normal_parabola(__global Parabola *obj, Ray ray, float t)
{
	float4		tmp;
	float4		x;
	float		a;

	tmp = (float4)(0.0f);
	if (obj)
	{
		tmp = ray.d * t + ray.o - obj->position;
		a = dot(tmp, obj->axis);
		x = obj->axis * (obj->a + a);
		tmp = normalize(tmp - x);
	}
	return (tmp);
}

double			intersect_torus(__global Torus *obj, Ray ray, float2 lim)
{
	float16		p;
	double8		poli;
	float4		x;
	t_root		tmp;
	double		t;

	if (!obj || !length(ray.d))
		return (INFINITY);
	x = ray.o - obj->position;
	p[0] = pown(obj->r2, 2);
	p[1] = dot(ray.d, x);
	p[2] = dot(x, x);
	p[3] = dot(obj->axis, ray.d);
	p[4] = dot(obj->axis, x);
	p[5] = 1.0 - pown(p[3], 2);
	p[6] = 2.0 * (p[1] - p[3] * p[4]);
	p[7] = p[2] - pown(p[4], 2);
	p[8] = p[2] + p[0] - pown(obj->r1, 2);
	poli = (double8)(1.0,
		4.0 * p[1],
		2.0 * p[8] + 4.0 * pown(p[1], 2) - 4.0 * p[0] * p[5],
		4.0 * p[1] * p[8] - 4.0 * p[0] * p[6],
		pown(p[8], 2) - 4.0 * p[0] * p[7],
		0.0, 0.0, 0.0);
	tmp = solve_qoe(poli);
	t = get_root(tmp, lim);
	return (t);
}

float4			normal_torus(__global Torus *obj, Ray ray, float t)
{
	float4		tmp;
	float4		x;
	float4		y;
	float		a;
	float		b;

	tmp = (float4)(0.0);
	if (obj)
	{
		x = ray.d * t + ray.o;
		a = dot(x - obj->position, obj->axis);
		b = sqrt(pown(obj->r1, 2) - pown(a, 2));
		y = x - obj->axis * a;
		tmp = (obj->position - y) * b / (obj->r2 - b);
		tmp = normalize(obj->axis * a - tmp);
	}
	return (tmp);
}

double			intersect_triangle(__global Triangle *obj, Ray ray, float2 lim)
{
	double		t;
	double4		delta;
	float4		a;
	float4		b;
	float4		c;

	if (!obj || !length(ray.d))
		return (INFINITY);
	a = obj->point_a - obj->point_b;
	b = obj->point_a - obj->point_c;
	c = obj->point_a - ray.o;
	delta.x = determinant(a, b, c);
	delta.y = determinant(c, b, ray.d);
	delta.z = determinant(a, c, ray.d);
	delta.w = determinant(a, b, ray.d);
	delta.x = get_root(solve_foe((double8)(0.0, 0.0, 0.0, delta.w, -delta.x, 0.0, 0.0, 0.0)), lim);
	delta.y = get_root(solve_foe((double8)(0.0, 0.0, 0.0, delta.w, -delta.y, 0.0, 0.0, 0.0)), lim);
	delta.z = get_root(solve_foe((double8)(0.0, 0.0, 0.0, delta.w, -delta.z, 0.0, 0.0, 0.0)), lim);
	if (delta.y > 0.0 && delta.z > 0.0 && delta.y + delta.z < 1.0)
		t = delta.x;
	else
		t = INFINITY;
	return (t);
}

float4			normal_triangle(__global Triangle *obj, Ray ray)
{
	float4		tmp;
	double		a;

	tmp = (float4)(0.0);
	if (obj)
	{
		tmp = normalize(cross(obj->point_a - obj->point_b, obj->point_a - obj->point_c));
		a = dot(tmp, ray.d);
		if (a > 0.0)
			tmp = -tmp;
	}
	return (tmp);
}

float4					ch_base_vec(float4 a, float4 b, float4 c)
{
	float4				tmp;

	tmp = (float4)(dot(a, b), dot(a, c), dot(a, cross(b, c)), 0.0);
	return (tmp);
}

t_root			limit_mobius(__global Mobius *obj, Ray ray, t_root tmp)
{
	float4		x;
	float4		o;
	float4		d;
	int			i;
	int			j;
	float		v;

	i = tmp.order;
	while (i > 0)
	{
		o = ch_base_vec(ray.o - obj->position, obj->axis_x, obj->axis_y);
		d = ch_base_vec(ray.d, obj->axis_x, obj->axis_y);
		x = o + d * convert_float(tmp.a[--i]);
		v = pown(sqrt(pown(x.x, 2) + pown(x.y, 2)) - obj->r, 2) + pown(x.z, 2);
		if (v > obj->a)
		{
			j = i;
			while (j < tmp.order - i)
				tmp.a[j++] = tmp.a[j + 1];
			tmp.a[j] = 0.0;
			tmp.order--;
		}
	}
	return (tmp);
}

double			intersect_mobius(__global Mobius *obj, Ray ray, float2 lim)
{
	double8		poli;
	t_root		tmp;
	double		t;
	float4		o;
	float4		d;
	double		r;

	if (!obj || !length(ray.d))
		return (INFINITY);
	o = ch_base_vec(ray.o - obj->position, obj->axis_x, obj->axis_y);
	d = ch_base_vec(ray.d, obj->axis_x, obj->axis_y);
	r = obj->r;
	poli = (double8)(0.0,
		pown(d.x, 2) * d.y + pown(d.y, 3) - 2.0 * pown(d.x, 2) * d.z
		- 2.0 * pown(d.y, 2) * d.z + d.y * pown(d.z, 2),
		2.0 * d.x * d.y * o.x - 4.0 * d.x * d.z * o.x + pown(d.x, 2) * o.y
		+ 3.0 * pown(d.y, 2) * o.y - 4.0 * d.y * d.z * o.y + pown(d.z, 2) * o.y
		- 2.0 * pown(d.x, 2) * o.z - 2.0 * pown(d.y, 2) * o.z + 2.0 * d.y * d.z * o.z
		- 2.0 * d.x * d.z * r,
		d.y * pown(o.x, 2) - 2.0 * d.z * pown(o.x, 2) + 2.0 * d.x * o.x * o.y
		+ 3.0 * d.y * pown(o.y, 2) - 2.0 * d.z * pown(o.y, 2) - 4.0 * d.x * o.x * o.z
		- 4.0 * d.y * o.y * o.z + 2.0 * d.z * o.y * o.z + d.y * pown(o.z, 2)
		- 2.0 * d.z * o.x * r - 2.0 * d.x * o.z * r - d.y * pown(r, 2),
		pown(o.x, 2) * o.y + pown(o.y, 3) - 2 * pown(o.x, 2) * o.z
		- 2.0 * pown(o.y, 2) * o.z + o.y * pown(o.z, 2)
		- 2.0 * o.x * o.z * r - o.y * pown(r, 2),
		0.0, 0.0, 0.0);
	tmp = solve_toe(poli);
	tmp = limit_mobius(obj, ray, tmp);
	t = get_root(tmp, lim);
	return (t);
}

float4			normal_mobius(__global Mobius *obj, Ray ray, float t)
{
	float4		tmp;
	float4		x;
	float4		y;
	float4		z;
	float4		sc;
	float4		o;
	float4		d;
	double		f;
	double		s;
	double		a;

	tmp = (float4)(0.0);
	if (obj)
	{
		o = ch_base_vec(ray.o - obj->position, obj->axis_x, obj->axis_y);
		d = ch_base_vec(ray.d, obj->axis_x, obj->axis_y);
		x = o + d * t;
		f = atan2(x.y, x.x);
		sc = (float4)(sin(f), cos(f), sin(f * 0.5), cos(f * 0.5));
		s = 0.0;
		if (fabs(sc.z) > EPS)
			s = x.z / sc.z;
		else if (fabs(sc.y) > EPS && fabs(sc.w) > EPS)
			s = (x.x / sc.y - obj->r) / sc.w;
		else if (fabs(sc.x) > EPS && fabs(sc.w) > EPS)
			s = (x.x / sc.x - obj->r) / sc.w;
		y = (float4)(
			0.5 * sc.y * sc.w,
			0.5 * sc.x * sc.w,
			0.5 * sc.z,
			0.0);
		z = (float4)(
			-sc.x + 0.5 * s * sc.x * sc.w - 0.25 * s * sc.y * sc.z,
			sc.y + 0.5 * s * sc.x * sc.w - 0.25 * s * sc.x * sc.z,
			0.25 * sc.w,
			0.0);
		tmp = normalize(cross(y, z));
		a = dot(tmp, d);
		if (a < 0.0)
			tmp = -tmp;
	}
	return (tmp);
}

float			intersect_object(__global Object *object, Ray ray, float2 lim);
float4			normal_object(__global Object *object, Ray ray, float t);
bool			find_intersection(IntersectionDesc *intersectionDesc, Ray ray, __global Object *objects, int numObjects, float2 lim);

float			intersect_object(__global Object *object, Ray ray, float2 lim)
{
	double		t;

	t = INFINITY;
	switch (object->type)
	{
		case SPHERE:
			t = intersect_sphere(&object->primitive.s, ray, lim);
			break;
		case PLANE:
			t = intersect_plane(&object->primitive.p, ray, lim);
			break;
		case DISK:
			t = intersect_disk(&object->primitive.d, ray, lim);
			break;
		case CONE:
			t = intersect_cone(&object->primitive.cone, ray, lim);
			break;
		case CYLINDER:
			t = intersect_cylinder(&object->primitive.cyl, ray, lim);
			break;
		case ELLIPS:
			t = intersect_ellipsoid(&object->primitive.el, ray, lim);
			break;
		case PARABOLA:
			t = intersect_parabola(&object->primitive.par, ray, lim);
			break;
		case TORUS:
			t = intersect_torus(&object->primitive.tor, ray, lim);
			break;
		case TRIANGLE:
			t = intersect_triangle(&object->primitive.tri, ray, lim);
			break;
		case MOBIUS:
			t = intersect_mobius(&object->primitive.mob, ray, lim);
			break;
	}
	return (convert_float(t));
}

float4			normal_object(__global Object *object, Ray ray, float t)
{
	switch (object->type)
	{
		case SPHERE:
			return (normal_sphere(&object->primitive.s, ray, t));
		case PLANE:
			return (normal_plane(&object->primitive.p, ray));
		case DISK:
			return (normal_disk(&object->primitive.d, ray));
		case CONE:
			return (normal_cone(&object->primitive.cone, ray, t));
		case CYLINDER:
			return (normal_cylinder(&object->primitive.cyl, ray, t));
		case ELLIPS:
			return (normal_ellipsoid(&object->primitive.el, ray, t));
		case PARABOLA:
			return (normal_parabola(&object->primitive.par, ray, t));
		case TORUS:
			return (normal_torus(&object->primitive.tor, ray, t));
		case TRIANGLE:
			return (normal_triangle(&object->primitive.tri, ray));
		case MOBIUS:
			return (normal_mobius(&object->primitive.mob, ray, t));
	}
	return ((float4)(0.0f));
}

bool			find_intersection(IntersectionDesc *intersectionDesc, Ray ray, __global Object *objects, int numObjects, float2 lim)
{
	intersectionDesc->intersected_obj = -1;
	intersectionDesc->normal = (float4)(0.0f);
	intersectionDesc->t = lim.y;
	int i = -1;
	while (++i < numObjects)
	{
		float t = intersect_object(&objects[i], ray, lim);
		if (t >= EPS && t < intersectionDesc->t)
		{
			intersectionDesc->t = t;
			intersectionDesc->intersected_obj = i;
			intersectionDesc->normal = normal_object(&objects[i], ray, t);
		}
	}
	return (intersectionDesc->intersected_obj != -1);
}

#define KERNEL_ENTRY 												\
	const int2 coord = (int2)(get_global_id(0), get_global_id(1)); 	\
	const int id = coord.x + width * coord.y;						\
	if (any(coord >= (int2)(width, height))) {						\
		return;														\
	}

__kernel void	GenerateRay(
	__global PixelDesc *pixelDescs,
	float4 camera_position,
	float4 camera_right,
	float4 camera_up,
	float4 camera_dir,
	int width,
	int height,
	int mode) {
	KERNEL_ENTRY

	float2 uv = (0.5f + convert_float2(coord)) / convert_float2((int2)(width, height));
	float2 ndc = uv * 2.0f - 1.0f;
	if ((mode >> 4) == 3)
		ndc *= pow(distance(ndc, (float2)(1.0f / width)), 2);

	pixelDescs[id].ray.o = camera_position;
	pixelDescs[id].ray.d = normalize(camera_dir + camera_right * ndc.x - camera_up * ndc.y);
	pixelDescs[id].radiance = (float4)(0.0f);
}

t_figure		closest_figure(IntersectionDesc closest, Ray ray, __global Object *objects, __global Texture *textures, int numObjects);
float4			reflect_ray(float4 normal, float4 ray);
float4			refract_ray(float4 normal, float4 ray, float n);
float4			find_radiance(t_figure fig, IntersectionDesc hit_point, Ray ray,__global Object *objects, __global Light *lights, __global Texture *textures, int numLights, int numObjects);

float			perlin_noise(float x, float y, float freq, int depth);
float			noise(float x, float y);
int				noise2(int x, int y);
float			lin_inter(float a, float b, float t);
float			smooth_inter(float x, float y, float t);
void			procedural_texture(t_figure *fig, __global Object *objects, __global Texture *textures);

__constant static int hash[] = {151,160,137,91,90,15,
		131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
		190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
		88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
		77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
		102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
		135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
		5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
		223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
		129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
		251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
		49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
		138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
	};

int		noise2(int x, int y)
{
	int tmp = hash[y % 256];
	return hash[(tmp + x) % 256];
}

float	lin_inter(float a, float b, float t)
{
	return a + t * (b - a);
}

float	smooth_inter(float x, float y, float t)
{
	return lin_inter(x, y, t * t * t * (t * (t * 6 - 15) + 10));
}

float	noise(float x, float y)
{
	int x_int = x;
	int y_int = y;
	float x_frac = x - x_int;
	float y_frac = y - y_int;
	int s = noise2(x_int, y_int);
	int t = noise2(x_int + 1, y_int);
	int u = noise2(x_int, y_int + 1);
	int v = noise2(x_int + 1, y_int + 1);
	float low = smooth_inter(s, t, x_frac);
	float high = smooth_inter(u, v, x_frac);
	return smooth_inter(low, high, y_frac);
}

float	perlin_noise(float x, float y, float freq, int depth)
{
	float	new_x;
	float	new_y;
	float	amp;
	float	res;
	float	div;
	int		i;

	i = 0;
	div = 0.0f;
	res = 0.0f;
	new_x = x * freq;
	new_y = y * freq;
	amp = 16.0f;
	depth = clamp(depth, 1, 20);
	while (i < depth)
	{
		div += 256 * amp;
		res += noise(new_x, new_y) * amp;
		amp /= 2;
		new_x *= 2;
		new_y *= 2;
		i++;
	}
	res /= div;
	return (res);
}

int             ft_convert(float t, int a);

int             ft_convert(float t, int a)
{
	return (convert_int(fabs(t)) % a);
}

float4				rot_q(float4 a, float4 b, float c);
float				cos_q(float4 a, float4 b);

float4				rot_q(float4 a, float4 b, float c)
{
	float4			tmp;
	float			cos_a;
	float			sin_a;

	cos_a = cos(c);
	sin_a = sin(c);
	tmp = a * cos_a + cross(b, a) * sin_a;
	tmp = tmp + b * (1 - cos_a) * dot(a, b);
	return (tmp);
}


float				cos_q(float4 a, float4 b)
{
	float			cos;
	float			mag_a;
	float			mag_b;

	mag_a = length(a);
	mag_b = length(b);
	if (!mag_a || !mag_b)
		return (1);
	cos = dot(a, b) / mag_a / mag_b;
	return (cos);
}

void			procedural_texture(t_figure *fig, __global Object *objects, __global Texture *textures)
{
	float4		n;
	float		u;
	float		v;
	float		edge;
	float4		result;
	float		h;
	float		len;
	int 		i;
	int 		j;
	int 		pos;
	float4		vect;
	float		alpha;
	float4		res;

//	fig->scale *= 10;
	if (fig->proced == CHECKERBOARD || fig->proced == BRICK || fig->proced == PERLIN || fig->proced == GRID || fig->proced == NORMAL_DISRUP)
		fig->scale = 10;
	if (fig->type == SPHERE)
	{
		n = normalize(fig->point - objects[fig->id].primitive.s.position);
		u = 0.5f + atan2(n.z, n.x) / M_PI_F * 0.5f;
		v = 0.5f - asin(n.y) / M_PI_F;
		if (fig->proced == CHECKERBOARD || fig->proced == BRICK || fig->proced == PERLIN || fig->proced == GRID || fig->proced == NORMAL_DISRUP)
		{
			u *= fig->scale;
			v *= fig->scale;
		}
	}
	else if (fig->type == PLANE)
	{
		vect = cross(fig->normal, ((float4){1.0f, 0.0f, 0.0f, 0.0f}));
		if (dot(vect, vect) < 0.001f)
			vect = (float4){0.0f, 1.0f, 0.0f, 0.0f};
		else
			vect = normalize(vect);
		vect = normalize(vect);
		if (fig->proced == BRICK || fig->proced == PERLIN || fig->proced == TEXTURE_1 || fig->proced == TEXTURE_2 || fig->proced == TEXTURE_3)
		{
			v = fabs(dot(fig->point, vect));
			u = fabs(dot(fig->point, (cross(vect, fig->normal))));
			v += 0.5f; // deleted symmetrical view of the procedural texture
		}
		else
		{
			u = dot(fig->point, vect);
			v = dot(fig->point, (cross(vect, fig->normal)));
		}
	}
	else if (fig->type == CYLINDER)
	{
		vect = cross((float4){0.0f, 1.0f, 0.0f, 0.0f}, objects[fig->id].primitive.cyl.axis);
		vect = normalize(vect);
		alpha = acos(cos_q((float4){0.0f, 1.0f, 0.0f, 0.0f}, objects[fig->id].primitive.cyl.axis));
		res = rot_q(fig->normal, vect, -alpha);
		if (fig->proced == BRICK || fig->proced == GRID || fig->proced == PERLIN || fig->proced == NORMAL_DISRUP)
			u = atan2(res.x, res.z) / (2 * M_PI_F) + 0.5f;
		else
			u = atan2(res.z, res.x) / (0.5f * M_PI_F) + 0.5f;
		h = dot(objects[fig->id].primitive.cyl.axis, (fig->point - objects[fig->id].primitive.cyl.position));
		v = h;
		if (fig->proced == CHECKERBOARD || fig->proced == BRICK || fig->proced == PERLIN || fig->proced == GRID || fig->proced == NORMAL_DISRUP)
		{
			u *= fig->scale;
			v *= fig->scale;
			if (fig->proced == BRICK || fig->proced == PERLIN)
			{
				v = fabs(v);
				u = fabs(u);
				u *= 2;
				v /= 2;
				v += 0.5f;
			}			
			if (fig->proced == GRID)
			{
				v /= 2;
				u += 0.5f;
			}
			if (fig->proced == NORMAL_DISRUP)
			{
				u *= 5;
				v /= 5;
			}
		}
	}
	else if (fig->type == CONE)
	{
		vect = cross((float4){0.0f, 1.0f, 0.0f, 0.0f}, objects[fig->id].primitive.cyl.axis);
		vect = normalize(vect);
		alpha = acos(cos_q((float4){0.0f, 1.0f, 0.0f, 0.0f}, objects[fig->id].primitive.cyl.axis));
		res = rot_q(fig->normal, vect, -alpha);
		if (fig->proced == BRICK || fig->proced == GRID || fig->proced == PERLIN || fig->proced == NORMAL_DISRUP)
			u = atan2(res.x, res.z) / (2 * M_PI_F) + 0.5f;
		else
			u = atan2(res.z, res.x) / (0.5f * M_PI_F) + 0.5f;
		len = length(fig->point - objects[fig->id].primitive.cone.position);
		v = fabs((objects[fig->id].primitive.cone.angle * len) / 5.0f);
		if (fig->proced == CHECKERBOARD || fig->proced == BRICK || fig->proced == PERLIN || fig->proced == GRID || fig->proced == NORMAL_DISRUP)
		{
			u *= fig->scale;
			v *= fig->scale;
			if (fig->proced == BRICK || fig->proced == PERLIN || fig->proced == NORMAL_DISRUP)
			{
				u *= 2;
				v *= 2;
			}
			if (fig->proced == GRID)
				u += 0.5f;
			if (fig->proced == TEXTURE_1)
				v *= 2;
		}
	}
	if (fig->proced == CHECKERBOARD)
		edge = ((int)floor(u) + (int)floor(v)) % 2 == 0;
	else if (fig->proced == GRID)
	{
		edge = fabs(sin(u * 10) + cos(v * 10));
		edge = clamp(edge, -1.0f, 1.0f);
	}
	else if (fig->proced == BRICK)
		edge = ((u - (int)u < 0.1f) && ((int)u & 0x01) == ((int)v & 0x01)) || (v - (int)v < 0.1f);
	else if (fig->proced == PERLIN)
	{
		edge = perlin_noise(u, v, 10.0f, 5); // perlin noise, freq = 10.0f, depth = 5;
		fig->normal.z = mix(fig->normal.z, edge, edge);
	}
	else if (fig->proced == TEXTURE_1)
	{
		if (fig->type == SPHERE)
			fig->scale /= 2.0f;
		if (fig->type == CONE)
			fig->scale /= 2.0f;
		i = ft_convert((u + fig->horiz_shift) / fig->scale * T_W, T_W);
		j = ft_convert((v + fig->vertic_shift) / fig->scale * T_W, T_W);
		pos = j * T_W + i;
		result = convert_float4(textures->a[pos].zyxw) / 255.0f;
	}
	else if (fig->proced == TEXTURE_2)
	{
		if (fig->type == SPHERE)
			fig->scale /= 2.0f;
		if (fig->type == CONE)
			fig->scale /= 2.0f;
		i = ft_convert((u + fig->horiz_shift) / fig->scale * T_W, T_W);
		j = ft_convert((v + fig->vertic_shift) / fig->scale * T_W, T_W);
		pos = j * T_W + i;
		result = convert_float4(textures->b[pos].zyxw) / 255.0f;
	}
	else if (fig->proced == TEXTURE_3)
	{
		i = ft_convert((u + fig->horiz_shift) / fig->scale * T_W, T_W);
		j = ft_convert((v + fig->vertic_shift) / fig->scale * T_W, T_W);
		pos = j * T_W + i;
		result = convert_float4(textures->c[pos].zyxw) / 255.0f;
	}
	if (fig->proced == NORMAL_DISRUP)
	{
		edge = sin(v * 10);
		fig->normal.z = mix(edge, fig->normal.z, edge);
	}
	else if (fig->proced == TEXTURE_1 || fig->proced == TEXTURE_2 || fig->proced == TEXTURE_3)
		fig->color = result;
	else
	{
		result = mix(fig->color, fig->color2, edge);
		fig->color = result;
	}
}

t_figure		closest_figure(IntersectionDesc closest, Ray ray, __global Object *objects, __global Texture *textures, int numObjects) {
	t_figure	fig;
	int			id;

	id = closest.intersected_obj;
	fig.point = ray.o + ray.d * closest.t;
	fig.normal = closest.normal;
	fig.reflect = objects[id].reflect;
	fig.transparency = objects[id].transparency;
	fig.refract = objects[id].refract;
	fig.type = objects[id].type;
	fig.id = id;
	fig.proced = objects[id].proced;
	fig.color = objects[id].color;
	fig.color2 = objects[id].color2;
	fig.scale = objects[id].scale;
	fig.horiz_shift = objects[id].horiz_shift;
	fig.vertic_shift = objects[id].vertic_shift;
	if (fig.proced != DEFAULT)
		procedural_texture(&fig, objects, textures);
	return (fig);
}

float4	reflect_ray(float4 normal, float4 ray)
{
	float4	reflect;

	reflect = ((2 * dot(normal, ray)) * normal) - ray;
	return (reflect);
}

float4	refract_ray(float4 normal, float4 ray, float n)
{
	float4	refract;

	float cos_theta = -dot(normal, ray);
	if (cos_theta < 0)
	{
		cos_theta *= -1;
		normal *= -1;
		n = 1.0f / n;
	}
	float k = 1 - n * n * (1 - cos_theta * cos_theta);
	if (k >= 0.0f)
	{
		refract = (n * ray) + ((n * cos_theta - sqrt(k)) * normal);
		refract = refract / length(refract);
	}
	else
		refract = (float4)(0.0f);
	return (refract);
}

float4					find_radiance(
	t_figure			fig,
	IntersectionDesc	hit_point,
	Ray					ray,
	__global Object		*objects,
	__global Light		*lights,
	__global Texture 	*textures,
	int					numLights,
	int					numObjects)
{
	IntersectionDesc	desc;
	int					intersectedObj;
	Ray					shadow_ray;
	Ray					light_ray;
	float4				normal;
	float4				radiance;
	float				factor;
	float				ambi = 0.0f;
	float				diff = 0.0f;
	float				spec = 0.0f;
	int					i = -1;
	bool				shadow;
	bool				k;
	float				t_max;
	bool				clos;
	t_figure			f;
	IntersectionDesc	closest_from_light;

	intersectedObj = hit_point.intersected_obj;
	if (intersectedObj != -1)
	{
		normal = fig.normal;
		shadow_ray.o = ray.o + ray.d * hit_point.t + normal * EPS;
		while (++i < numLights)
		{
			k = false;
			if (lights[i].type == SPHERE)
			{
				shadow_ray.d = lights[i].primitive.s.position - shadow_ray.o;
				t_max = fast_length(shadow_ray.d);
				shadow_ray.d /= t_max;
				light_ray.o = lights[i].primitive.s.position;
			}
			else if (lights[i].type == CONE)
			{
				shadow_ray.d = lights[i].primitive.cone.position - shadow_ray.o;
				t_max = fast_length(shadow_ray.d);
				shadow_ray.d /= t_max;
				k = -dot(shadow_ray.d, lights[i].primitive.cone.axis) < cos(lights[i].primitive.cone.angle);
				light_ray.o = lights[i].primitive.cone.position;
			}
			else if (lights[i].type == PLANE)
			{
				shadow_ray.d = -lights[i].primitive.p.normal;
				t_max = intersect_plane(&lights[i].primitive.p, shadow_ray, (float2)(EPS, INFINITY));
				k = dot(shadow_ray.d, lights[i].primitive.p.position - shadow_ray.o) < 0;
				light_ray.o = shadow_ray.o + t_max * shadow_ray.d;
			}
			light_ray.d = -shadow_ray.d;
			shadow = find_intersection(&desc, shadow_ray, objects, numObjects, (float2)(EPS, t_max)) || k;
			if (!shadow && (lights[i].type == SPHERE || lights[i].type == PLANE || lights[i].type == CONE))
			{
				factor = clamp(dot(normal, shadow_ray.d), 0.0f, 1.0f);
				diff += lights[i].intensity * factor;
				factor = clamp(dot(fast_normalize(ray.d - 2.0f * normal * dot(normal, ray.d)), shadow_ray.d), 0.0f, 1.0f);
				if (objects[intersectedObj].specular > 0)
					spec += lights[i].intensity * pown(factor, objects[intersectedObj].specular);
			}
			else
			{
				f = closest_figure(desc, ray, objects, textures, numObjects);
				clos = find_intersection(&closest_from_light, light_ray, objects, numObjects, (float2)(EPS, t_max));
				if (desc.intersected_obj != -1 && closest_from_light.intersected_obj == desc.intersected_obj)
				{
					if (f.transparency > 0.0f)
					{
						factor = clamp(dot(normal, shadow_ray.d), 0.0f, 1.0f);
						diff += f.transparency * lights[i].intensity * factor;
						factor = clamp(dot(fast_normalize(ray.d - 2.0f * normal * dot(normal, ray.d)), shadow_ray.d), 0.0f, 1.0f);
						if (objects[intersectedObj].specular > 0)
							spec += f.transparency * lights[i].intensity * pown(factor, objects[intersectedObj].specular);
					}
				}
			}
		}
		ambi = objects[intersectedObj].ambient;
		radiance = fig.color * (ambi + diff) + (float4)(0.4f) * spec;
	}
	else
		radiance = (float4)(0.0f);
	return (radiance);
}

__kernel void	Radiance(
	__global IntersectionDesc *intersectionDescs,
	__global PixelDesc *pixelDescs,
	__global Object *objects,
	__global Light *lights,
	__global Texture *textures,
	int numLights,
	int numObjects,
	int width,
	int height)
{
	KERNEL_ENTRY
	Ray					ray;
	int 				i = 1;
	int 				reflection_depth = 3;
	int 				refraction_depth = 3;	
	float4				res_color;
	t_figure			fig;
	t_figure			tmp_fig;
	IntersectionDesc	closest;
	IntersectionDesc	tmp_closest;
	float4				tmp_reflect;
	float4				tmp_refract;
	float4				reflect;
	float4				refract;
	float4				reflected_color;
	float4				refracted_color;
	Ray					tmp_ray;
	float4				tmp_color;
	float				previous_refl_coef;
	float				previous_transp_coef;

	ray = pixelDescs[id].ray;
	if (!find_intersection(&closest, ray, objects, numObjects, (float2)(EPS, INFINITY)))
		res_color = (float4)(0.0f);
	else
	{
		fig = closest_figure(closest, ray, objects, textures, numObjects);
		res_color = find_radiance(fig, closest, ray, objects, lights, textures, numLights, numObjects);
		if (fig.reflect > 0.0f)
		{
			i = 1;
			reflect = reflect_ray(fig.normal, -1.0f * ray.d);
			tmp_ray.o = fig.point;
			tmp_ray.d = reflect;
			while (i < reflection_depth)
			{
				if (!find_intersection(&tmp_closest, tmp_ray, objects, numObjects, (float2)(EPS, INFINITY)))
					tmp_color = (float4)(0.0f);
				else
				{
					previous_refl_coef = tmp_fig.reflect;
					tmp_fig = closest_figure(tmp_closest, tmp_ray, objects, textures, numObjects);
					tmp_color = find_radiance(tmp_fig, tmp_closest, tmp_ray, objects, lights, textures, numLights, numObjects);
					if (tmp_fig.reflect > 0.0f)
					{
						tmp_reflect = reflect_ray(tmp_fig.normal, -1.0f * tmp_ray.d);
						tmp_ray.o = tmp_fig.point;
						tmp_ray.d = tmp_reflect;
					}
					if (tmp_fig.reflect > 0.0f)
						tmp_color *= (1 - tmp_fig.reflect);
				}
				if (i == 1)
					reflected_color = tmp_color * (1 - tmp_fig.reflect);
				else
					reflected_color = tmp_color * (1 - tmp_fig.reflect) * previous_refl_coef + reflected_color;
				i++;
			}
		}
		if (fig.transparency > 0.0f)
		{
			i = 1;
			refract = refract_ray(fig.normal, ray.d, fig.refract);
			tmp_ray.o = fig.point;
			tmp_ray.d = refract;
			while (i < refraction_depth)
			{
				if (!find_intersection(&tmp_closest, tmp_ray, objects, numObjects, (float2)(EPS, INFINITY)))
					tmp_color = (float4)(0.0f);
				else
				{
					previous_transp_coef = tmp_fig.transparency;
					tmp_fig = closest_figure(tmp_closest, tmp_ray, objects, textures, numObjects);
					tmp_color = find_radiance(tmp_fig, tmp_closest, tmp_ray, objects, lights, textures, numLights, numObjects);
					if (tmp_fig.transparency > 0.0f)
					{
						tmp_refract = refract_ray(tmp_fig.normal, tmp_ray.d, fig.refract);
						tmp_ray.o = tmp_fig.point;
						tmp_ray.d = tmp_refract;
					}
					if (tmp_fig.transparency > 0.0f)
						tmp_color *= (1 - tmp_fig.reflect);
				}
				if (i == 1)
					refracted_color = tmp_color * (1 - tmp_fig.reflect);
				else
					refracted_color = tmp_color * (1 - tmp_fig.reflect) * previous_transp_coef + refracted_color;
				i++;
			}
		}
		if (fig.transparency > 0.0f || fig.reflect > 0.0f)
		{
			if (fig.transparency > 0.0f)
				res_color *= (1 - fig.transparency);
			if (fig.reflect > 0.0f)
				res_color *= (1 - fig.reflect);
			if (fig.transparency && fig.reflect)
				res_color = res_color + (refracted_color * (1 - fig.reflect) * fig.transparency + reflected_color * fig.reflect);
			else if (fig.transparency && fig.reflect == 0.0f)
				res_color = res_color + (refracted_color * (1 - fig.reflect) * fig.transparency);
			else if (fig.transparency == 0.0f && fig.reflect)
				res_color = res_color + (reflected_color * fig.reflect);
		}
	}
	pixelDescs[id].radiance = res_color;
}

float4			convert_px(float4 a, int x, int y, int mode);

float4			convert_px(float4 a, int x, int y, int mode)
{
	float4		tmp;
	float4		r = (float4)(0.393f, 0.769f, 0.189f, 1.0f);
	float4		g = (float4)(0.349f, 0.686f, 0.168f, 1.0f);
	float4		b = (float4)(0.272f, 0.534f, 0.131, 1.0f);
	float		t = 0.25f;
	int			k = 0x04;

	tmp = (float4)(0.0f, 0.0f, 0.0f, a.w);
	if (mode == 1)
	{
		t = (a.x + a.y + a.z) * TRC;
		tmp = (float4)(t, t, t, a.w);
	}
	else if (mode == 2)
		tmp = (float4)(dot(a, r), dot(a, g), dot(a, b), a.w);
	else if (mode == 3)
	{
		tmp = a - t;
		tmp = (float4)(	(float)((int)(tmp.x * k)),
						(float)((int)(tmp.y * k)),
						(float)((int)(tmp.z * k)),
						a.w);
		tmp = tmp * t + t;
	}
	else if (mode == 4)
		tmp = (float4)(1.0f) - a;
	else if (mode == 5)
		tmp = (float4)(	(a.x < 0.596f) ? 1.0f - a.x : a.x,
			(a.y < 0.455f) ? 1.0f - a.y : a.y,
			(a.z < 0.486f) ? 1.0f - a.z : a.z,
			a.w);
	else if (mode == 6)
		if (x & y & 1)
			tmp.x = a.x;
		else if	((x ^ y) & 1)
			tmp.y = a.y;		
		else
			tmp.z = a.z;
	else
		tmp = a;
	tmp.w = 1.0f;
	tmp = clamp(tmp, 0.0f, 1.0f);
	return (tmp);
}

__kernel void	SaveFrame(
	__global PixelDesc *pixelDescs,
	__global PixelDesc *pixelDescs_l,
	__global uchar4 *image,
	int width,
	int height,
	int mode) {
	KERNEL_ENTRY

	pixelDescs[id].radiance = convert_px(pixelDescs[id].radiance, coord.x, coord.y, mode & 0x0f);
	pixelDescs_l[id].radiance = convert_px(pixelDescs_l[id].radiance, coord.x, coord.y, mode & 0x0f);
	if ((mode >> 4) == 4)
		pixelDescs[id].radiance = pixelDescs_l[id].radiance;
	else if ((mode >> 4) == 1)
		pixelDescs[id].radiance = (pixelDescs[id].radiance + pixelDescs_l[id].radiance) * 0.5f;
	else if ((mode >> 4) == 2)
		pixelDescs[id].radiance.yz = pixelDescs_l[id].radiance.yz;
	image[id] = convert_uchar4(pixelDescs[id].radiance * 255.0f);
}
