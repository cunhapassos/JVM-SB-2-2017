/*
 * Compile assim: javac int_logico.java -target 1.2 -source 1.2
 */
public class testaimprime{
	public static void main(String args[]){

		long array[] = {4,5,6};
		short arrayshort[] = {4,5,6};
		boolean arraybool[] = {true,false,true};
		char arraychar[] = {'c','h','a','r'};
		String arrayString = "string";
		float arraydouble[] = {3.4f,3.5f,3.6f};
		byte arraybyte[] = {'b','y','t','e'};

		System.out.println(array);	
		System.out.println(arrayshort);	
		System.out.println(arraybool);	
		System.out.println(arraychar);	
		System.out.println(arrayString);	
		System.out.println(arraydouble);	
		System.out.println(arraybyte);

	}
}