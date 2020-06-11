#include "ft_ssl_sha256.h"

uint32_t	g_sk[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

uint32_t	rotr(uint32_t x, uint32_t n) {
    return (x >> n % 32) | (x << (32-n) % 32);
}

int			pad_chunk_sha256(char *chunk, uint64_t count)
{
	while ((1 + 64 + count) % SHA256_CHUNK_SIZE != 0)
		chunk[count++] = 0;
	return count;
}

void		step_sha256(void *ptr, t_sha256 *vars)
{
	uint32_t	i;
	uint32_t	s0;
	uint32_t	s1;
	uint32_t	ch;
	uint32_t	tmp1;
	uint32_t	tmp2;
	uint32_t	maj;
	t_sha256	v;
	uint32_t	*chunks;

	chunks = ft_memalloc(sizeof(uint32_t) * 64);
	ft_memcpy(chunks, ptr, SHA256_CHUNK_SIZE);
	v.a = vars->a;
	v.b = vars->b;
	v.c = vars->c;
	v.d = vars->d;
	v.e = vars->e;
	v.f = vars->f;
	v.g = vars->g;
	v.h = vars->h;

	for (i = 16; i < 64; ++i)
	{
        chunks[i] = chunks[i-16] + chunks[i-7] +
			(rotr(chunks[i-15], 7) ^ rotr(chunks[i-15], 18) ^ (chunks[i-15] >> 3)) +
			(rotr(chunks[i- 2], 17) ^ rotr(chunks[i- 2], 19) ^ (chunks[i- 2] >> 10));
	}

	for (i = 0; i < 64; ++i)
	{
		s1 = rotr(v.e, 6) ^ rotr(v.e, 11) ^ rotr(v.e, 25);
        ch = (v.e & v.f) ^ ((~v.e) & v.g);
        tmp1 = v.h + s1 + ch + g_sk[i] + chunks[i];
        s0 = rotr(v.a, 2) ^ rotr(v.a, 13) ^ rotr(v.a, 22);
        maj = (v.a & v.b) ^ (v.a & v.c) ^ (v.b & v.c);
        tmp2 = s0 + maj;
 
        v.h = v.g;
        v.g = v.f;
        v.f = v.e;
        v.e = v.d + tmp1;
        v.d = v.c;
        v.c = v.b;
        v.b = v.a;
        v.a = tmp1 + tmp2;
	}
	vars->a += v.a;
	vars->b += v.b;
	vars->c += v.c;
	vars->d += v.d;
	vars->e += v.e;
	vars->f += v.f;
	vars->g += v.g;
	vars->h += v.h;
}

void		final_print(t_sha256 *vars)
{
	int		i;
	char	*key;

	i = 1;
	key = "%.8x%.8x%.8x%.8x%.8x%.8x%.8x%.8x\n";
	if (*(char *)&i == 1)
		printf(key, vars->a, vars->b, vars->c, vars->d, vars->e, vars->f, vars->g, vars->h);
	else
		printf("SHIT");
	// printf(key, rev_sha256(vars->a), rev_sha256(vars->b), rev_sha256(vars->c), rev_sha256(vars->d), rev_sha256(vars->e));
}

void		sha256(t_env *env)
{
	int			fd;
	char		tmp[SHA256_CHUNK_SIZE + 1];
	t_sha256	*vars;
	uint64_t	count;
	uint64_t	size;

	fd = 0;
	vars = ft_memalloc(sizeof (t_sha256));

	vars->a = 0x6a09e667;
	vars->b = 0xbb67ae85;
	vars->c = 0x3c6ef372;
	vars->d = 0xa54ff53a;
	vars->e = 0x510e527f;
	vars->f = 0x9b05688c;
	vars->g = 0x1f83d9ab;
	vars->h = 0x5be0cd19;

	if (env->argc >= 3)
		e_error((fd = open(env->opt, O_RDONLY)) < 0, 0);
	ft_bzero(tmp, SHA256_CHUNK_SIZE + 1);
	while ((count = read(fd, tmp, SHA256_CHUNK_SIZE)))
	{
		tmp[count] = 0;
		size += count;
		if (count < SHA256_CHUNK_SIZE)
			break;
		step_sha256(tmp, vars);
		ft_bzero(tmp, SHA256_CHUNK_SIZE + 1);
	}
	close(fd);
	pad_chunk_sha256(tmp, count);
	tmp[count] |= 1 << 7;
	if (count >= 56) {
		step_sha256(tmp, vars);
		ft_bzero(tmp, MD5_CHUNK_SIZE + 1);
	}
	*((uint64_t*)&tmp[64 - 8]) = size * 8;

	step_sha256(tmp, vars);
	final_print(vars);
}