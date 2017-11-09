public class Parent {

  protected String output = "hallo";

  protected void setOutput(String output) {
    this.output = output;
  }

  public void print() {
    System.out.println(output );
  }
}