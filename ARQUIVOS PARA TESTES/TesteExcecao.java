public class TesteExcecao{

	public static void main(String[] args) {
		int a = 2;
		int b = 0;
	
		int c = dividir(a,b);
	
	}

	public static int dividir(int a, int b){
		int c = 0;
		try{
			c = a/b;
		}
		catch(ArithmeticException e){
			System.out.println(e.getMessage());
		}

		return(c);


	}
}