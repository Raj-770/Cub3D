typedef struct s_texture
{
    int     line_height;
    int     start;
    int     end;
    double  wall_x;
    double  step;
    int     pxl[2];
    double  pos;
}   t_texture;

typedef struct s_ray
{
	double	cam_x;
	double	dir[2];
	double	d_dist[2];
	int		pos[2];
	double	s_dist[2];
	int		step[2];
	int		hit_side[2];
	int		hit_axis;
	double	wall_dist;
	int		wall_hit;
}	t_ray;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

static void set_struct(t_texture *t, t_ray *r, t_vector *vec, t_game_data *g)
{
    t->line_height = (g->img->height) / r->wall_dist;
    t->start = (g->img->height / 2) - (t->line_height / 2);
    t->end = (g->img->height / 2) + (t->line_height / 2);
    if (t->start < 0)
        t->start = 0;
    if (t->end >= (int)(g->img->height))
        t->end = g->img->height - 1;
    if (r->hit_axis == X)
        t->wall_x = vec[POS].y + (r->wall_dist * r->dir[Y]);
    else
        t->wall_x = vec[POS].x + (r->wall_dist * r->dir[X]);
    t->wall_x -= floor(t->wall_x);
    t->pxl[X] = (int)(t->wall_x * (double)g->walls[r->wall_hit]->width);
    if ((r->hit_axis == X && r->dir[X] > 0) \
    || (r->hit_axis == Y && r->dir[Y] < 0))
        t->pxl[X] = g->walls[r->wall_hit]->width - t->pxl[X] - 1;
    t->step = (double)(g->walls[r->wall_hit]->height) / t->line_height;
    t->pos = (t->start - (g->img->height / 2) + (t->line_height / 2)) * t->step;
}
void    paint_walls(t_ray *r, short x, t_vector *vec, t_game_data *g)
{
    t_texture       t;
    int32_t         pxl;
    mlx_texture_t   *wall;
    wall = g->walls[r->wall_hit];
    set_struct(&t, r, vec, g);
    while (t.start < t.end)
    {
        t.pxl[Y] = t.pos;
        pxl = (t.pxl[Y] * wall->width + t.pxl[X]) * 4;
        mlx_put_pixel(g->img, x, t.start, ft_color(wall->pixels[pxl + R], \
        wall->pixels[pxl + G], wall->pixels[pxl + B]));
        t.pos += t.step;
        t.start++;
    }
}