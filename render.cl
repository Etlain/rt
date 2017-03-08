typedef struct	s_cam
{
	double3		pos;
	double3		dir;
}				t_cam;

typedef struct	s_ray
{
	double3		color;
	double3		a;
	double3		dir;
	double3		current;
	int			id;
	double		t;
}				t_ray;

typedef struct	s_light
{
	double3		pos;
	double3		color;
}				t_light;

typedef struct	s_object
{
	double3		color;
	double3		a;
	double3		b;
	double3		c;
	double		r;
	double		min;
	double		max;
	char		type;
}				t_object;

double3	limit_v(double3 v, double min, double max)
{
	if (v.x < min)
		v.x = min;
	else if (v.x > max)
		v.x = max;
	if (v.y < min)
		v.y = min;
	else if (v.y > max)
		v.y = max;
	if (v.z < min)
		v.z = min;
	else if (v.z > max)
		v.z = max;
	return (v);
}

double	get_t_a(double delta, double a, double b)
{
	double	t1;
	double	t2;

	if (delta == 0)
	{
		t1 = -b / (2 * a);
		return (t1);
	}
	else if (delta > 0)
	{
		t1 = (-b - sqrt(delta)) / (2 * a);
		t2 = (-b + sqrt(delta)) / (2 * a);
		if (t1 < t2)
			return (t1);
		return (t2);
	}
	return (-1);
}

double			ft_ctn(double a, double tmp)
{
	if (a >= 0 && tmp < 0)
		tmp = a;
	else if (a >= 0 && tmp >= 0 && a < tmp)
		tmp = a;
	return (tmp);
}

double			ft_condition(double4 res, int max)
{
	double	tmp;

	tmp = 0;
	if (max == 0)
		return (-1);
	if (max >= 1)
		tmp = res.x;
	if (max >= 2)
		tmp = ft_ctn(res.y, tmp);
	if (max >= 3)
		tmp = ft_ctn(res.z, tmp);
	if (max >= 4)
		tmp = ft_ctn(res.w, tmp);
	if (tmp <= 0.0)
		return (-1);
	return (tmp);
}

int				degree_2(double4 *pol, double4 *res)
{
	double	delta;

	delta = pol->y * pol->y - 4 * pol->x * pol->z;
	if (delta == 0)
	{
		res->x = -pol->y / (2 * pol->x);
		return (1);
	}
	else if (delta > 0)
	{
		res->x = (-pol->y + sqrt(delta)) / (2 * pol->x);
		res->y = (-pol->y - sqrt(delta)) / (2 * pol->x);
		return (2);
	}
	return (0);
}

double	fill_pq_delta(double2 *pq, double4 *pol)
{
	double delta;

	pq->x = (pol->z / pol->x) - ((pol->y * pol->y) / (3.0 * pol->x * pol->x));
	pq->y = ((2.0 * pol->y * pol->y * pol->y)
	/ (27.0 * pol->x * pol->x * pol->x))
	+ (pol->w / pol->x) - ((pol->y * pol->z)
	/ (3.0 * pol->x * pol->x));
	delta = pq->y * pq->y + ((4.0 * pq->x * pq->x * pq->x) / 27.0);
	return (delta);
}

double		res_neg(double4 *res, double2 pq, double4 *pol)
{
	res->x = (2.0 * sqrt(-pq.x / 3.0) * cos((1.0 / 3.0) *
	acos((-pq.y / 2.0) * sqrt(27.0 / (-pq.x * pq.x * pq.x)))
	+ (2.0 * 0 * M_PI) / 3.0)) - pol->y / (3.0 * pol->x);
	res->y = (2.0 * sqrt(-pq.x / 3.0) * cos((1.0 / 3.0) *
	acos((-pq.y / 2.0) * sqrt(27.0 / (-pq.x * pq.x * pq.x)))
	+ (2.0 * 1 * M_PI) / 3.0)) - pol->y / (3.0 * pol->x);
	res->z = (2.0 * sqrt(-pq.x / 3.0) * cos((1.0 / 3.0) *
	acos((-pq.y / 2.0) * sqrt(27.0 / (-pq.x * pq.x * pq.x)))
	+ (2.0 * 2 * M_PI) / 3.0)) - pol->y / (3.0 * pol->x);
	return (3);
}

double		res_eq(double4 *res, double2 pq, double4 *pol)
{
	res->x = ((3.0 * pq.y) / pq.x) - (pol->y / (3.0 * pol->x));
	res->y = -(3.0 * pq.y) / pq.x - pol->y / (3.0 * pol->x);
	return (2);
}

void	cubic(double4 *pol, double4 *res, int x, int y)
{
	double	delta;
	double2	pq;
	double	u;
	double	v;
	double	sol;

	sol = 0;
	delta = fill_pq_delta(&pq, pol);
	if (delta > 0)
	{
		u = cbrt((-pq.y + sqrt(delta)) / 2.0);
		v = cbrt((-pq.y - sqrt(delta)) / 2.0);
		res->x = u + v - pol->y / (3 * pol->x);
		sol = 1;
	}
	else if (delta == 0)
		sol = res_eq(res, pq, pol);
	else if (delta < 0)
		sol = res_neg(res, pq, pol);
}

double3		set_pqr(double3 pqr, double4 pol, double u)
{
	pqr.x = (-3.0 * pol.y * pol.y) / (8.0 * pol.x * pol.x)
	+ pol.z / pol.x;
	pqr.y = ((pol.y * pol.y * pol.y) / 8.0) / (pol.x * pol.x * pol.x)
	- ((pol.y * pol.z) / 2.0) / (pol.x * pol.x) + pol.w / pol.x;
	pqr.z = -3.0 * pow((pol.y / 4.0) / pol.x, 4.0)
	+ ((pol.z * (pol.y / 4.0) * (pol.y) / 4.0)) / (pol.x * pol.x * pol.x)
	- ((pol.y * pol.w) / 4.0) / (pol.x * pol.x)
	+ u / pol.x;
	return (pqr);
}

void	set_cubic(double3 *pqr, double4 pol, double u, double4 *p1)
{
	pqr->x = (-3.0 * pol.y * pol.y) / (8.0 * pol.x * pol.x)
	+ pol.z / pol.x;
	pqr->y = ((pol.y * pol.y * pol.y) / 8.0) / (pol.x * pol.x * pol.x)
	- ((pol.y * pol.z) / 2.0) / (pol.x * pol.x) + pol.w / pol.x;
	pqr->z = -3.0 * pow((pol.y / 4.0) / pol.x, 4.0)
	+ ((pol.z * (pol.y / 4.0) * (pol.y) / 4.0)) / (pol.x * pol.x * pol.x)
	- ((pol.y * pol.w) / 4.0) / (pol.x * pol.x)
	+ u / pol.x;
	p1->x = 8.0;
	p1->y = -4.0 * pqr->x;
	p1->z = -8.0 * pqr->z;
	p1->w = 4.0 * pqr->z * pqr->x - pqr->y * pqr->y;
}

int		set_res(double3 pqr, double4 *p1, double4 *res)
{
	double4	res2;
	double	y;
	double	a0;
	double	b0;
	int		sol;
	int		sol2;

	y = res->x;
	res->x = 0;
	res->y = 0;
	res->z = 0;
	res->w = 0;
	a0 = sqrt(-pqr.x + 2.0 * y);
	if (2 * y - pqr.x != 0)
		b0 = -pqr.y / (2.0 * a0);
	else
		b0 = sqrt(y * y - pqr.z);
	p1->x = 1.0;
	p1->y = -a0;
	p1->z = y - b0;
	sol = degree_2(p1, res);
	p1->x = 1.0;
	p1->y = a0;
	p1->z = y + b0;
	sol2 = degree_2(p1, &res2);
	if (sol == 0)
	{
		res->x = res2.x;
		res->y = res2.y;
	}
	else if (sol == 1)
	{
		res->y = res2.x;
		res->z = res2.y;
	}
	else if (2)
	{
		res->z = res2.x;
		res->w = res2.y;
	}
	return (sol + sol2);
}

int			quartic(double4 pol, double u, double4 *res, int x, int y)
{
	double4	p1;
	double3	pqr;
	int		sol;

	set_cubic(&pqr, pol, u, &p1);
	cubic(&p1, res, x, y);
	sol = set_res(pqr, &p1, res);
	if (sol == 0)
		return (0);
	res->x = res->x - pol.y / (4.0 * pol.x);
	res->y = res->y - pol.y / (4.0 * pol.x);
	res->z = res->z - pol.y / (4.0 * pol.x);
	res->w = res->w - pol.y / (4.0 * pol.x);
	return (sol);
}

double4 fill_p(t_ray *ray, t_object obj, double3 pos)
{
    double4 p;

    p.x = pow(ray->dir.x, 4) + pow(ray->dir.y, 4) + pow(ray->dir.z, 4);
    p.y = 4 * (pow(ray->dir.x, 3) * pos.x + pow(ray->dir.y, 3) * pos.y
    + pow(ray->dir.z, 3) * pos.z);
    p.z = 6 * (pow(ray->dir.x, 2) * pow(pos.x, 2) + pow(ray->dir.y, 2)
    * pow(pos.y, 2) + pow(ray->dir.z, 2) * pow(pos.z, 2))
    - 5 * (pow(ray->dir.x, 2) + pow(ray->dir.y, 2) + pow(ray->dir.z, 2));
    p.w = 4 * (pow(pos.x, 3) * ray->dir.x + pow(pos.y, 3) * ray->dir.y
    + pow(pos.z, 3) * ray->dir.z)
    - 10 * (ray->dir.x * pos.x + ray->dir.y * pos.y + ray->dir.z * pos.z);
    return (p);
}

double check_ct(t_ray *ray, t_object obj, int x, int y)
{
		double4 p;
		double u;
		double tmp;
		double3 pos;
		double4 res;
		int	 sol;

		pos = ray->a - obj.a;
        p = fill_p(ray, obj, pos);
		u = pow(pos.x, 4) + pow(pos.y, 4) + pow(pos.z, 4)
    	- 5 * (pos.x * pos.x + pos.y * pos.y + pos.z * pos.z) + obj.r;
		sol = quartic(p, u, &res, x, y);
		tmp = ft_condition(res, sol);
		return (tmp);
}

double3			normal_ct(t_ray *ray, __global t_object *obj)
{
	double3	res;
	double3	pos;
	double	a;

	pos = ray->a - obj->a;
	res = ray->dir * ray->t + pos;
	res.x = 4 * pow(res.x, 3) - 10 * res.x;
	res.y = 4 * pow(res.y, 3) - 10 * res.y;
	res.z = 4 * pow(res.z, 3) - 10 * res.z;
	return (res);
}

double4	fill_p2(t_ray *ray, t_object obj, double3 pos)
{
	double4 p;

	p.x = pow(ray->dir.x * ray->dir.x + ray->dir.y * ray->dir.y
	+ ray->dir.z * ray->dir.z, 2);
	p.y = 4 * (ray->dir.x * ray->dir.x + ray->dir.y * ray->dir.y
	+ ray->dir.z * ray->dir.z) * (ray->dir.x * pos.x + ray->dir.y
	* pos.y + ray->dir.z * pos.z);
	p.z = 2 * (ray->dir.x * ray->dir.x + ray->dir.y * ray->dir.y
	+ ray->dir.z * ray->dir.z) * (pos.x * pos.x + pos.y * pos.y
	+ pos.z * pos.z + obj.max * obj.max - obj.min * obj.min)
	+ 4 * pow(ray->dir.x * pos.x + ray->dir.y * pos.y
	+ ray->dir.z * pos.z, 2) - 4 * obj.max * obj.max
	* (ray->dir.x * ray->dir.x * obj.b.x + ray->dir.y * ray->dir.y * obj.b.y
	+ ray->dir.z * ray->dir.z * obj.b.z);
	p.w = 4 * (ray->dir.x * pos.x + ray->dir.y * pos.y
	+ ray->dir.z * pos.z) * (pos.x * pos.x + pos.y * pos.y
	+ pos.z * pos.z + obj.max * obj.max - obj.min * obj.min)
	- 8 * obj.max * obj.max * (ray->dir.x * pos.x * obj.b.x
	+ ray->dir.y * pos.y * obj.b.y + ray->dir.z * pos.z * obj.b.z);
	return (p);
}

double			check_torus(t_ray *ray, t_object obj)
{
	double3 pos;
	double4 p;
	double z;
	double4 res;
	int nbr;
	double tmp;

	pos = ray->a - obj.a;
	p = fill_p2(ray, obj, pos);
	z = pow(pos.x * pos.x + pos.y * pos.y
	+ pos.z * pos.z + obj.max * obj.max - obj.min * obj.min, 2)
	- 4 * obj.max * obj.max * (pos.x * pos.x * obj.b.x + pos.y * pos.y
	* obj.b.y + pos.z * pos.z * obj.b.z);
	nbr = quartic(p, z, &res, 0, 0);
	tmp = ft_condition(res, nbr);
	return (tmp);
}

double check_ellipsoid(t_ray *ray, t_object obj)
{
	double3 pos;
	double4 res;
	double4 p;
    double 	a;
	int		sol;

	pos = ray->a - obj.a;
	p.x = (ray->dir.x * ray->dir.x) / (obj.b.x * obj.b.x)
    + (ray->dir.y * ray->dir.y) / (obj.b.y * obj.b.y)
	+ (ray->dir.z * ray->dir.z) / (obj.b.z * obj.b.z);
	p.y = 2 * ((ray->dir.x * pos.x) / (obj.b.x * obj.b.x)
    + (ray->dir.y * pos.y) / (obj.b.y * obj.b.y)
    + (ray->dir.z * pos.z) / (obj.b.z * obj.b.z));
	p.z = (pos.x * pos.x) / (obj.b.x * obj.b.x)
    + (pos.y * pos.y) / (obj.b.y * obj.b.y)
    + (pos.z * pos.z) / (obj.b.z * obj.b.z) - 1;
	sol = degree_2(&p, &res);
	a = ft_condition(res, sol);
	return (a);
}

double3 		normal_ellipsoid(t_ray *ray, __global t_object *obj)
{
	double3	res;
	double3 pos;

	pos = ray->a - obj->a;
	res = ray->dir * ray->t + pos;
	res *= 2 / obj->b * obj->b;
	return (res);
}

double3				normal_torus(t_ray *ray, __global t_object *obj)
{
	double3	res;
	double3	pos;
	double	r;
	double	a;

	pos = ray->a - obj->a;
	r = obj->max;
	res = ray->dir * ray->t + pos;
	a = 1.0 - (r / sqrt(res.x * res.x + res.y * res.y + res.z * res.z));
	obj->b.x != 0 ? (res.x *= a * obj->b.x) : 0;
	obj->b.y != 0 ? (res.y *= a * obj->b.y) : 0;
	obj->b.z != 0 ? (res.z *= a * obj->b.z) : 0;
	return (res);
}

double	check_sphere(t_ray *ray, t_object obj)
{
	double	a;
	double	b;
	double	c;

	a = (ray->dir.x * ray->dir.x) + (ray->dir.y * ray->dir.y) +
	(ray->dir.z * ray->dir.z);
	b = 2 * (ray->dir.x * (ray->a.x - obj.a.x) + ray->dir.y *
	(ray->a.y - obj.a.y) + ray->dir.z * (ray->a.z - obj.a.z));
	c = (ray->a.x - obj.a.x) * (ray->a.x - obj.a.x) +
	(ray->a.y - obj.a.y) * (ray->a.y - obj.a.y) +
	(ray->a.z - obj.a.z) * (ray->a.z - obj.a.z) - (obj.r * obj.r);
	return (get_t_a((b * b) - 4 * a * c, a, b));
}

double	check_cylinder(t_ray *ray, t_object obj)
{
	double3	v;
	double	a;
	double	b;
	double	c;
	double	delta;

	obj.b = normalize(obj.b);
	v = ray->a - obj.a;
	a = dot(ray->dir, ray->dir) - pow(dot(ray->dir, obj.b), 2);
	b = 2 * (dot(ray->dir, v) - dot(ray->dir, obj.b) * dot(v, obj.b));
	c = dot(v, v) - pow(dot(v, obj.b), 2) - (obj.r * obj.r);
	delta = get_t_a((b * b) - 4 * a * c, a, b);
	if (delta >= 0.1)
		return (delta);
	return (-1);
}

double	check_plane(t_ray *ray, t_object *obj)
{
	double3	v;
	double3	o;
	double	t;
	double	d;

	o.x = 0;
	o.y = 0;
	o.z = 0;
	v = obj->a - o;
	obj->c = normalize(obj->c);
	d = length(v);
	t = -(obj->c.x * ray->a.x + obj->c.y * ray->a.y +
	obj->c.z * ray->a.z + d) / (obj->c.x * ray->dir.x +
	obj->c.y * ray->dir.y + obj->c.z * ray->dir.z);
	if (t >= 0.001)
		return (t);
	return (-1);
}

double	check_cone(t_ray *ray, t_object obj)
{
	double3	x;
	double	a;
	double	b;
	double	c;
	double	k;

	obj.b = normalize(obj.b);
	x = ray->a - obj.a;
	k = tan((obj.r / 2) / (180 / M_PI));
	a = dot(ray->dir, ray->dir) - (1 + k * k) *
	pow(dot(ray->dir, obj.b), 2);
	b = 2 * (dot(ray->dir, x) - ((1 + k * k) *
	dot(ray->dir, obj.b) * dot(x, obj.b)));
	c = dot(x, x) - ((1 + k * k) * pow(dot(x, obj.b), 2));
	c = (b * b) - 4 * a * c;
	k = get_t_a(c, a, b);
	if (k >= 0.01)
		return (k);
	return (-1);
}

double	check_triangle(t_ray *ray, t_object *obj)
{
	double3	p;
	double	det;
	double	u;
	double	v;
	double	t;

	p = cross(ray->dir, obj->c - obj->a);
	det = dot(obj->b - obj->a, p);
	if (det > -0.000001 && det < 0.000001)
		return (-1);
	det = 1.0 / det;
	u = dot(ray->a - obj->a, p) * det;
	if (u < 0 || u > 1.0)
		return (-1);
	p = cross(ray->a - obj->a, obj->b - obj->a);
	v = dot(ray->dir, p) * det;
	if (v < 0 || u + v > 1.0)
		return (-1);
	t = dot(obj->c - obj->a, p) * det;
	if (t > 0.000001)
		return (t);
	return (-1);
}

double	check_intersection(t_ray *ray, t_object obj, int x, int y)
{
	double	res;

	res = -1;
	if (obj.type == 1)
		res = check_sphere(ray, obj);
	else if (obj.type == 2)
		res = check_cylinder(ray, obj);
	else if (obj.type == 3)
		res = check_plane(ray, &obj);
	else if (obj.type == 4)
		res = check_cone(ray, obj);
	else if (obj.type == 5)
		res = check_triangle(ray, &obj);
	else if (obj.type == 6)
		res = check_torus(ray, obj);
	else if (obj.type == 7)
		res = check_ct(ray, obj, x, y);
	else if (obj.type == 8)
		res = check_ellipsoid(ray, obj);
	return (res);
}

void	intersection(t_ray *ray, __global t_object *obj, int nbobj, int x, int y)
{
	double	res;
	int		i;

	i = 0;
	res = -1;
	while (i < nbobj)
	{
		res = check_intersection(ray, obj[i], x, y);
		if (res >= 0 && ray->t != -1 && res < ray->t)
		{
			ray->id = i;
			ray->t = res;
		}
		else if (res >= 0 && ray->t == -1)
		{
			ray->id = i;
			ray->t = res;
		}
		i++;
	}
}

void		set_vrep(double3 d, double3 v[3])
{
	v[2] = normalize(d);
	if (fabs(v[2].y) == 1)
	{
		v[0].x = 1;
		v[1].z = -v[2].y;
		return ;
	}
	v[0].x = v[2].z;
	v[0].z = -v[2].x;
	v[1].y = sqrt(v[2].x * v[2].x + v[2].z * v[2].z);
	v[1].x = -v[2].x / (fabs(v[2].x) + fabs(v[2].z)) * v[2].y;
	v[1].z = -v[2].z / (fabs(v[2].x) + fabs(v[2].z)) * v[2].y;
}

void		get_normal(t_ray *ray, __global t_object *obj)
{
	double3	v;
	double	c;

	if (obj->type == 1)
		obj->c = ray->current - obj->a;
	else if (obj->type == 2)
	{
		c = length(ray->current - obj->a) * dot(normalize(obj->b), normalize(ray->current - obj->a));
		obj->c = (obj->b * -c) + (ray->current - obj->a);
	}
	else if (obj->type == 4)
	{
		c = length(ray->current - obj->a) / dot(normalize(obj->b),
		normalize(ray->current - obj->a));
		obj->c = (obj->b * -c) + (ray->current - obj->a);
	}
	else if (obj->type == 6)
		obj->c = normal_torus(ray, obj);
	else if (obj->type == 7)
		obj->c = normal_ct(ray, obj);
	else if (obj->type == 8)
		obj->c = normal_ellipsoid(ray, obj);
}

double3		get_normal_other(t_ray *ray, __global t_object *obj, t_light l)
{
	double3	n;

	if (obj->type == 5)
	{
		n = cross(obj->a - obj->b, obj->a - obj->c);
		if (dot(n, ray->current - l.pos) > 0)
			n = -n;
	}
	return (n);
}

void		light(t_light l, t_ray *ray, __global t_object *obj)
{
	double3	v;
	double3	n;
	double3	lp;
	double3	r;
	double	d;
	int		t;

	ray->color = obj->color + l.color;
	ray->current = ray->a + (ray->dir * ray->t);
	v = l.pos - ray->current;
	v = normalize(v);
	get_normal(ray, obj);
	n.x = obj->c.x;
	n.y = obj->c.y;
	n.z = obj->c.z;
	if (obj->type == 5)
		n = get_normal_other(ray, obj, l);
	n = normalize(n);
	d = dot(v, n);
	if (d < 0 || d > 1)
		d = 0;
	ray->color = ray->color * d;
	lp = normalize(ray->current - l.pos);
	r = lp + ((n * 2) * dot(-n, lp));
	r = normalize(r);
	d = pow(d, 200);
	if (d > 0)
	{
		ray->color = ray->color + (ray->color * d);
	}

}

void		check_light(__global t_light *l, t_ray *ray, __global t_object *obj, int nbl)
{
	double3	color;
	double	part;
	int		i;

	i = 0;
	part = (double)(1 / (double)nbl);
	color.x = 0;
	color.y = 0;
	color.z = 0;
	while (i < nbl)
	{
		light(l[i], ray, obj);
		color = color + ray->color;
		color = color * 0.75;
		i++;
	}
	ray->color = limit_v(color, 0, 255);
}

__kernel void	render_gpu( __global int 		*pixels,
							__global t_cam		*cam,
							__global t_object	*obj,
							__global int		*nbobj,
							__global t_light	*light,
							__global int		*nbl)
{
	private	int		gid = get_global_id(0);
	private	int		x = gid % 800;
	private	int		y = gid / 800;
	private int		i = (y * (800 * 4)) + (x * 4);
	private	double	ret;
	private	double3	v[3];
	t_ray			ray;

	v[0].x = 0;
	v[0].y = 0;
	v[0].z = 0;
	v[1].x = 0;
	v[1].y = 0;
	v[1].z = 0;
	v[2].x = 0;
	v[2].y = 0;
	v[2].z = 0;
	set_vrep(cam->dir, v);
	ray.a = cam->pos;
	ray.dir = normalize(((v[0] * (x - 800 / 2)) + (v[1] * (600 / 2 - y))) + (v[2] * (800 / 2)));

	ray.id = -1;
	ray.t = -1;
	intersection(&ray, obj, *nbobj, x, y);
	if (ray.id != -1)
	{
		check_light(light, &ray, &obj[ray.id], *nbl);
		pixels[i] = ray.color.x;
		pixels[i + 1] = ray.color.y;
		pixels[i + 2] = ray.color.z;
	}
}
