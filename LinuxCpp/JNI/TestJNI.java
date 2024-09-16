public class TestJNI {
    static {System.loadLibrary("JNItest");} // libJNItest.so
    private native String NativeMessage(String message); // method from C++ library

    private java.lang.String javaMethod(java.lang.String message) {
        System.out.print(message);
        System.out.print(" <= from TestJNI.javaMethod()\n");

        java.lang.String ret = "Return Message From javaMethod << hello from falca\n";
        return ret;
    }

    public static void main(String[] args) {
        TestJNI mObj = new TestJNI(); // create new instance
        System.out.print("----- start java TestJNI class -----\n");

        String javaFuncRet = mObj.javaMethod("This is the Java method message");
        System.out.print(javaFuncRet);
        // System.out.print(" <= from TestJNI.main()\n");

        String cppFunction = mObj.NativeMessage("This is the Native method message");
        System.out.print(cppFunction);
        // System.out.print(" <= from TestJNI.main()\n");
    } 
}
