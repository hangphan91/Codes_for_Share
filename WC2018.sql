
/*
Database Systems - CSCI 3360
Project 3	Convert ER Diagram to Relational Schema 
			and implement the database via Oracle DDL
Members: Hang Phan, Hassan Khan, Taylor Nguyen
*/

DROP TABLE Groups CASCADE CONSTRAINTS;
DROP TABLE Team CASCADE CONSTRAINTS;
DROP TABLE Championships CASCADE CONSTRAINTS;
DROP TABLE Achievements CASCADE CONSTRAINTS;
DROP TABLE Team_Stat CASCADE CONSTRAINTS;
DROP TABLE Player CASCADE CONSTRAINTS;
DROP TABLE Play_In CASCADE CONSTRAINTS;
DROP TABLE Score_Goal CASCADE CONSTRAINTS;
DROP TABLE Player_Stat CASCADE CONSTRAINTS;
DROP TABLE Matches CASCADE CONSTRAINTS;
DROP TABLE Awards CASCADE CONSTRAINTS;
DROP TABLE YellowCard CASCADE CONSTRAINTS;

/*Relations*/
CREATE TABLE Groups
(
	Identifier				CHAR(1),
	First_place				VARCHAR2(20),
	Runner_up				VARCHAR2(20),
	CONSTRAINT groups_identifier_pk PRIMARY KEY(Identifier)
);

CREATE TABLE Team
(
	Name					VARCHAR2(20),
	FIFA_ranking			NUMBER(3) CONSTRAINT team_ranking_uk UNIQUE,
	Manager					VARCHAR2(20),
	GroupID					CHAR(1),
	CONSTRAINT team_name_pk PRIMARY KEY(Name)
);

CREATE TABLE Team_Stat
(
	Tname					VARCHAR2(20),
	Qualified_campaign 		NUMBER(2),
	First_stage 			NUMBER(2),
	Semifinal				NUMBER(2),
	Final					NUMBER(2),
	CONSTRAINT teamstat_tname_pk PRIMARY KEY(Tname)
);
CREATE TABLE Player
(
	Fname					VARCHAR2(20),
	Lname 					VARCHAR2(20),
	Team 					VARCHAR2(20),
	Jersey					NUMBER(2),
	Position				VARCHAR2(20),
	Bdate 					DATE,
	Height 					NUMBER(4,1),
	Caps 					NUMBER(4),
	Goals 					NUMBER(4),
	Match_red_card  		NUMBER(2),
	CONSTRAINT player_team_jer_pk PRIMARY KEY(Team,Jersey)
);

CREATE TABLE Play_In 
(
	Team 					VARCHAR2(20),
	MatchID 				NUMBER(2),
	CONSTRAINT playin_team_match_pk PRIMARY KEY(Team,MatchID)
);

CREATE TABLE Score_Goal
(
	Team 					VARCHAR2(20),
	Jersey 					NUMBER(2),
	MatchID 				NUMBER(2),
	Time_scored 			NUMBER(3),
	CONSTRAINT scoregoal_team_jer_match_pk PRIMARY KEY(Team, Jersey, MatchID)
);

CREATE TABLE Player_Stat
(
	Team 					VARCHAR2(20),
	Jersey 					NUMBER(2),
	Red 					NUMBER(2),
	Yellow 					NUMBER(2),
	Offsides 				NUMBER(2),
	Fouls 					NUMBER(3),
	CONSTRAINT playerstat_team_jer_pk PRIMARY KEY(Team, Jersey)
);

create table Matches
(
	ID 						NUMBER(2),
	Location 				VARCHAR2(30),
	Game_date 				DATE,
	Game_time 				CHAR(5),
	Referee					VARCHAR2(30),
	CONSTRAINT matches_ID_pk PRIMARY KEY(ID)
);

CREATE TABLE Awards
(
	Award_name 				VARCHAR2(30),
	Sponsor 				VARCHAR2(20),
	Team_winner 			VARCHAR2(20),
	Pteam_winner 			VARCHAR2(20),
	Pjersey_winner			NUMBER(2),
	CONSTRAINT award_name_pk PRIMARY KEY(Award_name)
);

CREATE TABLE YellowCard
(
	Team_yellow				VARCHAR2(20),
	Jersey_yellow			NUMBER(2),
	MatchID_yellow			NUMBER(2),
	CONSTRAINT YellowCard_pk PRIMARY KEY(Team_yellow, Jersey_yellow, MatchID_yellow)
);

/*Linking the foreign keys to the respective relations*/

/*Constraints for Team*/
ALTER TABLE Team
ADD CONSTRAINT team_fk FOREIGN KEY (GroupID)
REFERENCES Groups(Identifier);

/*Constraints for Team_Stat*/
ALTER TABLE Team_Stat
ADD CONSTRAINT team_stat_fk FOREIGN KEY (Tname)
REFERENCES Team(Name);

/*Constraints for Player*/
ALTER TABLE Player
ADD CONSTRAINT player_fk1 FOREIGN KEY (Team)
REFERENCES Team(Name);

ALTER TABLE Player
ADD CONSTRAINT player_fk2 FOREIGN KEY (Match_red_card)
REFERENCES Matches(ID);

/*Constraints for Player_Stat*/
ALTER TABLE Player_Stat
ADD CONSTRAINT player_stat_fk FOREIGN KEY (Team,Jersey)
REFERENCES Player(Team,Jersey);

/*Constraints for Awards*/
ALTER TABLE Awards
ADD CONSTRAINT award_fk1 FOREIGN KEY (Team_winner)
REFERENCES Team(Name);

ALTER TABLE Awards
ADD CONSTRAINT award_fk3 FOREIGN KEY (Pteam_winner,Pjersey_winner)
REFERENCES Player(Team,Jersey);

/*Constraints for Play_In*/
ALTER TABLE Play_In
ADD CONSTRAINT play_in_fk1 FOREIGN KEY (Team)
REFERENCES Team(Name);

ALTER TABLE Play_In
ADD CONSTRAINT play_in_fk2 FOREIGN KEY (MatchID)
REFERENCES Matches(ID);

/*Constraints for Score_Goal*/
ALTER TABLE Score_Goal
ADD CONSTRAINT score_goal_fk2 FOREIGN KEY (MatchID)
REFERENCES Matches(ID);

ALTER TABLE Score_Goal
ADD CONSTRAINT score_goal_fk3 FOREIGN KEY (Team,Jersey)
REFERENCES Player(Team,Jersey);

ALTER TABLE YellowCard
ADD CONSTRAINT yellow_card_fk2 FOREIGN KEY (MatchID_yellow)
REFERENCES Matches(ID);

/*Constraints for YellowCard*/
ALTER TABLE YellowCard
ADD CONSTRAINT yellow_card_fk3 FOREIGN KEY (Team_yellow,Jersey_yellow)
REFERENCES Player(Team,Jersey);

/*Checkpoint creating relations*/
DESCRIBE Groups;
DESCRIBE Team;
DESCRIBE Championships;
DESCRIBE Achievements;
DESCRIBE Team_Stat;
DESCRIBE Player;
DESCRIBE Play_In;
DESCRIBE Score_Goal;
DESCRIBE Player_Stat;
DESCRIBE Matches;
DESCRIBE Awards;
DESCRIBE YellowCard;