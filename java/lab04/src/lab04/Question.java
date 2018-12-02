package lab04;


public class Question {
	
	private int id;
	private String questionTopic;
	private String [] possiblAanswers = new String[4];
	private int correctAnswer;
	private static int uniqueId = 0;
	Question(String _title, String A,String B, String C, String D, int _correctAns ){
		
		questionTopic = _title;
		possiblAanswers[0] = A;
		possiblAanswers[1] = B;
		possiblAanswers[2] = C;
		possiblAanswers[3] = D;
		correctAnswer = _correctAns;
		this.id = Question.uniqueId;
		Question.uniqueId++;
	}
	
	@Override
	public String toString() {
		
		return id+1 + ". " + questionTopic;
	}
	
}
