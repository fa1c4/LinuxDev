public class TestJNI {
    static {System.loadLibrary("JNItest");} // libJNItest.so
    private native String NativeMessage(String message); // method from C++ library

    private java.lang.String value;
    private void setValue(java.lang.String val) {
        value = val;
        System.out.print(val);
        System.out.print(" <= from TestJNI.setValue()\n");
    }

    public static void main(String[] args) {
        TestJNI mObj = new TestJNI(); // create new instance
        System.out.print("----- start java TestJNI class -----\n");

        String cppFunction = mObj.NativeMessage("This is the Native method message");
        System.out.print(cppFunction);
        // System.out.print(" <= from TestJNI.main()\n");

        System.out.print(mObj.value);
        System.out.print(" <= from TestJNI.main()\n");
    } 
}
