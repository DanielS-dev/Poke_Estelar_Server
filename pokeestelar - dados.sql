-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Tempo de geração: 17/06/2026 às 12:56
-- Versão do servidor: 10.4.32-MariaDB
-- Versão do PHP: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Banco de dados: `pokeestelar`
--

--
-- Despejando dados para a tabela `accounts`
--

INSERT INTO `accounts` (`id`, `name`, `password`, `secret`, `type`, `premdays`, `lastday`, `email`, `creation`) VALUES
(2766, 'teste', 'e0f68134d29dc326d115de4c8fab8700a3c4b002', NULL, 1, 9999, 1781691080, 'teste@teste.com', 1781689970);

--
-- Despejando dados para a tabela `players`
--

INSERT INTO `players` (`id`, `name`, `group_id`, `account_id`, `level`, `vocation`, `health`, `healthmax`, `experience`, `lookbody`, `lookfeet`, `lookhead`, `looklegs`, `looktype`, `lookaddons`, `maglevel`, `mana`, `manamax`, `manaspent`, `soul`, `town_id`, `posx`, `posy`, `posz`, `conditions`, `cap`, `sex`, `lastlogin`, `lastip`, `save`, `skull`, `skulltime`, `lastlogout`, `blessings`, `onlinetime`, `deletion`, `balance`, `offlinetraining_time`, `offlinetraining_skill`, `stamina`, `skill_fist`, `skill_fist_tries`, `skill_club`, `skill_club_tries`, `skill_sword`, `skill_sword_tries`, `skill_axe`, `skill_axe_tries`, `skill_dist`, `skill_dist_tries`, `skill_shielding`, `skill_shielding_tries`, `skill_fishing`, `skill_fishing_tries`) VALUES
(2985, 'Teste', 1, 2766, 147, 0, 945, 945, 51867540, 68, 76, 78, 58, 1970, 0, 0, 60, 60, 0, 100, 1, 639, 848, 7, '', 400, 1, 1781693216, 16777343, 1, 0, 0, 1781693723, 0, 1485, 0, 0, 43200, -1, 2520, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0);

--
-- Despejando dados para a tabela `player_deaths`
--

INSERT INTO `player_deaths` (`player_id`, `time`, `level`, `killed_by`, `is_player`, `mostdamage_by`, `mostdamage_is_player`, `unjustified`, `mostdamage_unjustified`) VALUES
(2985, 1781693211, 150, 'Rhyhorn', 0, 'Rhyhorn', 0, 0, 0);

--
-- Despejando dados para a tabela `player_items`
--

INSERT INTO `player_items` (`player_id`, `pid`, `sid`, `itemtype`, `count`, `attributes`) VALUES
(2985, 2, 101, 26820, 1, ''),
(2985, 3, 102, 1988, 1, ''),
(2985, 6, 103, 8922, 1, ''),
(2985, 7, 104, 38681, 1, ''),
(2985, 8, 105, 38680, 1, ''),
(2985, 9, 106, 38682, 1, ''),
(2985, 11, 107, 2270, 1, ''),
(2985, 12, 108, 2263, 1, ''),
(2985, 102, 109, 2148, 13, 0x0f0d),
(2985, 102, 110, 27645, 10, 0x0f0a),
(2985, 102, 111, 26662, 100, 0x0f64),
(2985, 102, 112, 27642, 100, 0x0f64),
(2985, 102, 113, 26661, 1, 0x2278017b5b22706f6b654c6f6f6b446972225d203d20312c5b2265766870225d203d20302c5b22706f6b654e616d65225d203d202246656e6e656b696e222c5b22636434225d203d20313738313639333330312e352c5b22706f6b654c6576656c225d203d20362c5b22706f6b65457870657269656e6365225d203d20323630302c5b22706f6b654d61784865616c7468225d203d203436302c5b22657661746b225d203d20302c5b226576646566225d203d20302c5b226576706f696e7473225d203d203330302c5b2265766b696c6c73225d203d20302c5b22756e69717565225d203d20312c5b22706f6b654c6f7665225d203d20312c5b22636431225d203d20313738313639333239392e352c5b22636432225d203d20313738313639333239382e352c5b22636433225d203d20313738313639333239372c5b22706f6b654865616c7468225d203d203130303030302c5b22706f6b65426f6f7374225d203d20302c5b2269734265696e6755736564225d203d20302c7d),
(2985, 105, 114, 38687, 1, ''),
(2985, 105, 115, 38686, 1, ''),
(2985, 105, 116, 38688, 1, ''),
(2985, 105, 117, 38684, 1, ''),
(2985, 105, 118, 38690, 1, ''),
(2985, 105, 119, 38685, 1, ''),
(2985, 105, 120, 38683, 1, ''),
(2985, 105, 121, 38689, 1, ''),
(2985, 105, 122, 26611, 1, ''),
(2985, 105, 123, 26610, 1, ''),
(2985, 105, 124, 26616, 1, ''),
(2985, 105, 125, 26613, 1, ''),
(2985, 105, 126, 26612, 1, ''),
(2985, 105, 127, 26615, 1, ''),
(2985, 105, 128, 26609, 1, ''),
(2985, 105, 129, 26614, 1, '');

--
-- Despejando dados para a tabela `player_storage`
--

INSERT INTO `player_storage` (`player_id`, `key`, `value`) VALUES
(2985, 5009, 1),
(2985, 5021, 512),
(2985, 30018, 1),
(2985, 63001, 1),
(2985, 65001, 0),
(2985, 65003, 0),
(2985, 65004, 0),
(2985, 65005, 0),
(2985, 65006, 0),
(2985, 65007, 0),
(2985, 65008, 0),
(2985, 65009, 0),
(2985, 65010, 0),
(2985, 65011, 0),
(2985, 65012, 0),
(2985, 65013, 0),
(2985, 65014, 0),
(2985, 65015, 0),
(2985, 65016, 0),
(2985, 65018, 0),
(2985, 65019, 0),
(2985, 65020, 0),
(2985, 65021, 0),
(2985, 65022, 0),
(2985, 65023, 0),
(2985, 65024, 0),
(2985, 65025, 0),
(2985, 65026, 0),
(2985, 65027, 0),
(2985, 65028, 0),
(2985, 65033, 0),
(2985, 65034, 0),
(2985, 65035, 0),
(2985, 65036, 0),
(2985, 65037, 0),
(2985, 65038, 0),
(2985, 65039, 0),
(2985, 65040, 0),
(2985, 65041, 0),
(2985, 91000, 0),
(2985, 91014, 0),
(2985, 92000, 0),
(2985, 92001, 0),
(2985, 92002, 0),
(2985, 92003, 0),
(2985, 92004, 0),
(2985, 92005, 0),
(2985, 92006, 0),
(2985, 92007, 0),
(2985, 92008, 0),
(2985, 92009, 0),
(2985, 92010, 0),
(2985, 92011, 0),
(2985, 92012, 0),
(2985, 92013, 0),
(2985, 92014, 0),
(2985, 92015, 0),
(2985, 92016, 0),
(2985, 180567074, 0),
(2985, 180567111, 0),
(2985, 180567653, 0);

--
-- Despejando dados para a tabela `znote_accounts`
--

INSERT INTO `znote_accounts` (`id`, `account_id`, `ip`, `created`, `points`, `cooldown`, `active`, `activekey`, `flag`, `secret`) VALUES
(2767, 2766, 0, 1781689970, 0, 0, 1, 995151919, 'br', NULL);
--
-- Despejando dados para a tabela `znote_players`
--

INSERT INTO `znote_players` (`id`, `player_id`, `created`, `hide_char`, `comment`) VALUES
(2986, 2985, 1781690327, 0, '');
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
