from numpy import *
from numpy.linalg import *

def minor(mat, i, j):
		mat_len = len(mat)
		i_range = list(range(0, mat_len))
		i_range.remove(i)
		j_range = list(range(0, mat_len))
		j_range.remove(j)
		return mat[transpose(array([j_range])), array([i_range])]

def minor_mat(mat):
	minor_mat = []
	mat_len = len(mat)

	k = 0
	for j in range(0, mat_len):
		for i in range(0, mat_len):
			if (k % 2) == 0:
				minor_mat.append(round(det(minor(mat, i, j))))
			else:
				minor_mat.append(-round(det(minor(mat, i, j))))
			k += 1
	return matrix(minor_mat).reshape(mat_len, mat_len)

def inverse_det(mat, mod):
	d = round(det(mat) % mod)
	for x in range(1, mod):
		if ((d * x) % mod == 1):
			return x
	return None

def adjugate_mat(mat):
	return transpose(minor_mat(mat))

def modular_inverse(mat, mod):
	inverse = inverse_det(mat, mod)
	if inverse:
		return inverse_det(mat, mod) * adjugate_mat(mat) % mod
	else:
		return None