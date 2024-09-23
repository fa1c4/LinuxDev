import pCpplib

print("pCpplib.mMessage() ->", pCpplib.mMessage())
print("pCpplib.mAdd() ->", pCpplib.mAdd(2, 33))

T1 = pCpplib.mClass("Testing cpp integrated class by fa1c4")
print("name =", T1.name)
T1.name = "Testing the name modification"
print("name =", T1.name)

T1.Set(0.3000000000004)
print("Get() 0.3 ->", T1.Get())
