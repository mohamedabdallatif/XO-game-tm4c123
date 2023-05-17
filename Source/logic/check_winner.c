extern int scoreX, scoreO;

char check_winner (char grid[], char turn){
	char player = turn;
	int i;
	// check winning within row 1 or 2 or 3
	for(i = 1; i <= 7; i = i + 3)
	{
		if(grid[i] == player && grid[i + 1] == player && grid[i + 2] == player)
		{
			if(player=='X') scoreX++;
			else scoreO++;
			
			return 1;
		}
	}
	
	// check winning within column 1 or 2 or 3
	for(i = 1; i <= 3; i = i + 1)
	{
		if(grid[i] == player && grid[i + 3] == player && grid[i + 6] == player)
		{
			if(player=='X') scoreX++;
			else scoreO++;
			return 1;
		}
	}
	
	// check winning within main diagonal
	if(grid[1] == player && grid[5] == player && grid[9] == player)
	{
		if(player=='X') scoreX++;
		else scoreO++;
		return 1;
	}
	
	// check winning within seconadry diagonal
	if(grid[3] == player && grid[5] == player && grid[7] == player)
	{
		if(player=='X') scoreX++;
		else scoreO++;
		return 1;
	}
	
	return 0; //no one won!
}
