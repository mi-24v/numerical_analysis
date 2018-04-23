import sympy

EPS = 0.001

def gauss_jordan(functions, symbols, values):
	print("functions")
	print(functions, end="\n\n")
	pivot = 0
	for i,(f,s) in enumerate(zip(functions,symbols)):#tuple (index ,[function_i])
		pivot = f.coeff(s)
		if abs(pivot) < EPS:#pivot check
			print("ERROR:too small pivot")
			return None
		#normalize
		functions[i] = functions[i] / pivot
		values[i] = values[i] / pivot
		#hakidashi
		for k in enumerate(functions):
			delta = functions[k[0]].coeff(s)
			if i == k[0]:
				pass
			else:
				functions[k[0]] -= delta * functions[i]
				values[k[0]] -= delta * values[i]
	return (functions,values)

#main
sympy.var("x,y,z")
#left side
functions = [2*x +y +3*z,x + 3*y + 2*z,3*x +2*y + z]
#right side
values = [13, 13, 10]
print("solve equations.")
ans = gauss_jordan(functions, [x,y,z], values)
if ans is None:
	print("no solution.")
else:
	for i in range(len(ans[0])):
		print(str(ans[0][i])+" = "+str(ans[1][i]))
print()
print("get inverse matrix.")
#Redefine
functions = [2*x +y +3*z,x + 3*y + 2*z,3*x +2*y + z]
values = [x, y, z]# unit matrix

ans = gauss_jordan(functions, [x,y,z], values)
if ans is None:
	print("no solution.")
else:
	for i in ans[1]:
		if i % 3 == 0:
			print(str(i), end="")
		else:
			print(str(i))

