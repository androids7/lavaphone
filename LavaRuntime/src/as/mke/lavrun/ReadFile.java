package as.mke.lavrun;

import java.io.*;
import java.nio.charset.Charset;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;
import java.util.zip.ZipInputStream;
import java.util.*;

public class ReadFile {
    public static InputStream readFile(String path,String filename) throws IOException {
       // String path = "F:\\*******\\201707\\78641695079026649.zip";
	   
	   
	   /*
        ZipFile zf = new ZipFile(path);
		InputStream ine=null;
        InputStream in = new BufferedInputStream(new FileInputStream(path));
        Charset gbk = Charset.forName("utf8");
        ZipInputStream zin = new ZipInputStream(in,gbk);
        ZipEntry ze;
        while((ze = zin.getNextEntry()) != null){
			
			
			
		if(ze.getName().equals(filename)){
            //    BufferedReader br = new BufferedReader(
				ine=zf.getInputStream(ze);
				
              
            }
            
			
			}
     //  zin.closeEntry();
    */
	
	
		InputStream ine=null;
	
		Charset gbk = Charset.forName("utf8");
        ZipFile zip = new ZipFile(new File(path), gbk);
        for (Enumeration entries = zip.entries(); entries.hasMoreElements();) {
            ZipEntry entry = (ZipEntry) entries.nextElement();
            String zipEntryName = entry.getName();
			
			if(zipEntryName.equals(filename)){
			
            ine = zip.getInputStream(entry);
			}
			/*
            String outPath = (descDir + zipEntryName).replaceAll("\\*", "/");
            // 判断路径是否存在,不存在则创建文件路径
            File file = new File(outPath.substring(0, outPath.lastIndexOf('/')));
            if (!file.exists()) {
                file.mkdirs();
            }
            // 判断文件全路径是否为文件夹,如果是上面已经上传,不需要解压
            if (new File(outPath).isDirectory()) {
                continue;
            }
            // 输出文件路径信息
            System.out.println(outPath);

            OutputStream out = new FileOutputStream(outPath);
            byte[] buf1 = new byte[1024];
            int len;
            while ((len = in.read(buf1)) > 0) {
                out.write(buf1, 0, len);
            }
            in.close();
            out.close();
	*/
	
	}
	return ine;
	
	}
	}
