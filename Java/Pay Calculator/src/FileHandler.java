import java.nio.file.*;
import java.io.IOException;

public class FileHandler
{
	public FileHandler() {}
	public void writeToFile(String filePath, String content) 
	{
		try
		{
			Path file = Path.of(filePath);
			Files.writeString(file, content);
		}catch(IOException e)
		{
			System.out.println("No file found");
		}
	}
}