The Party Planning Problem is best solved using the Graph data structure. 

The Academy Award Planning Committee is planning a party of Actors. 
They have an initial list of Actors they would like to invite. 
However, if any actor knows more than k people already invited they too become invited.
What is the final list of invited Actors.

Input:
  text document with Actors, year of movie, and movie in each line 
  text document with list of Actors initially invited to Party.
Output:
  text document with names of Actors invited to exclusive party
  
  
This particular problem is best solved with a graph and priority queue structure.
From the list of actors we create a Graph and connections. 
Then, read through the list of inital invitees, and invite anyone with over k connections
repeat sending invites until there are no more to be sent. 
