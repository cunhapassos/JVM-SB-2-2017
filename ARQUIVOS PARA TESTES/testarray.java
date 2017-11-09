/*
 * Compile assim: javac int_logico.java -target 1.2 -source 1.2
 */
public class testarray{
	public static void main(String args[]){

		int array[] = {4,5,6};
		boolean arraybool[] = {true,false,true};
		long arraylong[] = {255,255,255};
		short arrayshort[] = {4,5,6};
		char arraychar[] = {'c','h','a'};
		byte arraybyte[] = {10,20,30};
		double arraydouble[] = {3.4,3.5,3.6};
		float arrayfloat[] = {3.4f,3.5f,3.6f};


		for(int j = 0; j < array.length; j++){
			System.out.println(array[j]);
		}

		for(int j = 0; j < arraybool.length; j++){
			System.out.println(arraybool[j]);
		}

		for(int j = 0; j < arraylong.length; j++){
			System.out.println(arraylong[j]);
		}
		
		for(int j = 0; j < arrayshort.length; j++){
			System.out.println(arrayshort[j]);
		}

		for(int j = 0; j < arraychar.length; j++){
			System.out.println(arraychar[j]);
		}
			for(int j = 0; j < arraybyte.length; j++){
			System.out.println(arraybyte[j]);
		}
			for(int j = 0; j < arraydouble.length; j++){
			System.out.println(arraydouble[j]);
		}
			for(int j = 0; j < arrayfloat.length; j++){
			System.out.println(arrayfloat[j]);
		}


	}
}